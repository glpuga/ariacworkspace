/* Copyright [2021] <TheItalianJob>
 * Author: Gerardo Puga
 */

// standard library
#include <utility>

// tijcore
#include <logger/logger.hpp>
#include <tijcore/tasks/ModelTrayAccessSpaceManager.hpp>
#include <tijcore/tasks/RemoveBrokenPartTask.hpp>

namespace tijcore {

namespace {

constexpr std::chrono::seconds timeout_{120};
}

RemoveBrokenPartTask::RemoveBrokenPartTask(
    const ResourceManagerInterface::SharedPtr &resource_manager,
    const Toolbox::SharedPtr &toolbox,
    ResourceManagerInterface::ManagedLocusHandle &&target,
    ResourceManagerInterface::PickAndPlaceRobotHandle &&robot)
    : resource_manager_{resource_manager}, toolbox_{toolbox},
      target_{std::move(target)}, robot_{std::move(robot)} {}

RobotTaskOutcome RemoveBrokenPartTask::run() {
  auto &robot = *robot_.resource();
  auto scene = toolbox_->getSceneConfigReader();
  RobotTaskOutcome result{RobotTaskOutcome::TASK_FAILURE};

  tijcore::PartTypeId part_type_id;
  {
    auto [part_type, broken] = target_.resource()->model();
    (void)broken;
    part_type_id = part_type.type();
  }

  const auto target_parent_name = target_.resource()->parentName();

  ModelTrayAccessSpaceManager model_tray_access_manager(*resource_manager_,
                                                        robot);

  // clear exclusion zones to enable movement to a safe spot regardless of where
  // we are located
  model_tray_access_manager.clearAllExclusionZones();

  if (!robot.getInSafePoseNearTarget(target_.resource()->pose()) ||
      !model_tray_access_manager.releaseAccess()) {
    ERROR("{} failed to get in resting pose", robot.name());
  } else if (!model_tray_access_manager.getAccessToModel(target_parent_name,
                                                         timeout_)) {
    ERROR("{} failed to setup access constraints to target", robot.name());
  } else if (!robot.getToGraspingPoseHint(target_.resource()->pose())) {
    ERROR("{} failed to get closer to target", robot.name());
  } else if (!robot.getInLandingSpot(target_.resource()->pose())) {
    ERROR(
        "{} failed to get into the approximation pose to remove a broken part",
        robot.name());
  } else if (!robot.graspPartFromAbove(target_.resource()->pose(),
                                       part_type_id)) {
    ERROR("{} failed to pick up the broken part while trying to remove it",
          robot.name());
  } else if (!robot.getInSafePoseNearTarget(target_.resource()->pose()) ||
             !robot.gripperHasPartAttached() ||
             !model_tray_access_manager.releaseAccess()) {
    ERROR("{} failed to get the broken part ready for transport to the bucket",
          robot.name());
  } else if (!robot.getToGraspingPoseHint(scene->getDropBucketPose())) {
    ERROR("{} failed to get closer to target", robot.name());
  } else if (!robot.getInLandingSpot(scene->getDropBucketPose())) {
    ERROR("{} failed to get in the approximation pose to drop the broken "
          "part into the bucket",
          robot.name());
  } else if (!robot.dropPartWhereYouStand()) {
    ERROR("{} failed to drop the broken part into the bucket", robot.name());
  } else {
    result = RobotTaskOutcome::TASK_SUCCESS;
    // create an empty pose anywhere, we just need it to make the part info
    // dissapear
    auto limbo = ManagedLocus::CreateEmptySpace("drop_bucket",
                                                scene->getDropBucketPose());
    ManagedLocus::TransferPartFromHereToThere(*target_.resource(), limbo);
    INFO("{} successfully removed a broken part and placed it into the "
         "bucket",
         robot.name());
  }

  // if we failed the task at some point, we lost certainty about where the
  // source part is
  if (result != RobotTaskOutcome::TASK_SUCCESS) {
    *target_.resource() = ManagedLocus::CreateEmptySpace(
        target_.resource()->parentName(), target_.resource()->pose());
  }

  // try to get in a resting pose to remove the robot from the way
  robot.dropPartWhereYouStand();
  robot.getInSafePose();
  model_tray_access_manager.releaseAccess();
  return result;
}

void RemoveBrokenPartTask::halt() {
  auto &robot = *robot_.resource();
  robot.cancelAction();
}

} // namespace tijcore
