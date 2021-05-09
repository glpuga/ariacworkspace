/* Copyright [2021] <Ekumen>
 * Author: Gerardo Puga
 */

// standard library
#include <string>
#include <vector>

// project
#include <tijchallenger/SceneConfigReader.hpp>
#include <tijcore/utils/angles.hpp>

namespace tijchallenger {

namespace {

constexpr char world_frame_id_[] = "world";

} // namespace

using tijcore::utils::angles::degreesToRadians;

const std::string &SceneConfigReader::getWorldFrameId() const {
  static const std::string data{world_frame_id_};
  return data;
};

const tijcore::RelativePose3 &SceneConfigReader::getDropBucketPose() const {
  static const tijcore::RelativePose3 data{
      world_frame_id_,
      tijcore::Pose3{tijcore::Position::fromVector(-2.2, 0.0, 1.0), {}}};
  return data;
}

const std::vector<SceneConfigReader::BinData> &
SceneConfigReader::getListOfBins() const {
  static const std::vector<BinData> data{
      {"bin1", "bin1_frame", "agv12_access_space",
       tijcore::WorkRegionId::kitting},
      {"bin2", "bin2_frame", "agv12_access_space",
       tijcore::WorkRegionId::kitting},
      {"bin3", "bin3_frame", "agv12_access_space",
       tijcore::WorkRegionId::assembly},
      {"bin4", "bin4_frame", "agv12_access_space",
       tijcore::WorkRegionId::assembly},
      {"bin5", "bin5_frame", "agv34_access_space",
       tijcore::WorkRegionId::kitting},
      {"bin6", "bin6_frame", "agv34_access_space",
       tijcore::WorkRegionId::kitting},
      {"bin7", "bin7_frame", "agv34_access_space",
       tijcore::WorkRegionId::assembly},
      {"bin8", "bin8_frame", "agv34_access_space",
       tijcore::WorkRegionId::assembly},
  };
  return data;
}

const std::vector<SceneConfigReader::DeviceData> &
SceneConfigReader::getListOfLogicalCameras() const {
  static const std::vector<SceneConfigReader::DeviceData> data{
      {"logical_camera_bin_agv1", "logical_camera_bin_agv1_frame"},
      {"logical_camera_bin_agv2", "logical_camera_bin_agv2_frame"},
      {"logical_camera_bin_agv3", "logical_camera_bin_agv3_frame"},
      {"logical_camera_bin_agv4", "logical_camera_bin_agv4_frame"},
      {"logical_camera_as1", "logical_camera_as1_frame"},
      {"logical_camera_as2", "logical_camera_as2_frame"},
      {"logical_camera_as3", "logical_camera_as3_frame"},
      {"logical_camera_as4", "logical_camera_as4_frame"},
      {"logical_camera_agv1_as1", "logical_camera_agv1_as1_frame"},
      {"logical_camera_agv1_as2", "logical_camera_agv1_as2_frame"},
      {"logical_camera_agv2_as1", "logical_camera_agv2_as1_frame"},
      {"logical_camera_agv2_as2", "logical_camera_agv2_as2_frame"},
      {"logical_camera_agv3_as3", "logical_camera_agv3_as3_frame"},
      {"logical_camera_agv3_as4", "logical_camera_agv3_as4_frame"},
      {"logical_camera_agv4_as3", "logical_camera_agv4_as3_frame"},
      {"logical_camera_agv4_as4", "logical_camera_agv4_as4_frame"},
  };
  return data;
}

const std::vector<SceneConfigReader::DeviceData> &
SceneConfigReader::getListOfQualityControlSensors() const {
  static const std::vector<SceneConfigReader::DeviceData> data{
      {"quality_control_sensor_1", "quality_control_sensor_1_frame"},
      {"quality_control_sensor_2", "quality_control_sensor_2_frame"},
      {"quality_control_sensor_3", "quality_control_sensor_3_frame"},
      {"quality_control_sensor_4", "quality_control_sensor_4_frame"},
  };
  return data;
}

const std::vector<SceneConfigReader::DeviceData> &
SceneConfigReader::getListOfAgvs() const {
  static const std::vector<SceneConfigReader::DeviceData> data{
      {"agv1", "kit_tray_1", "agv12_access_space"},
      {"agv2", "kit_tray_2", "agv12_access_space"},
      {"agv3", "kit_tray_3", "agv34_access_space"},
      {"agv4", "kit_tray_4", "agv34_access_space"},
  };
  return data;
}

const std::vector<SceneConfigReader::DeviceData> &
SceneConfigReader::getListOfAssemblyStations() const {
  static const std::vector<DeviceData> data{
      {"as1", "briefcase_1", "as1_access_space"},
      {"as2", "briefcase_2", "as2_access_space"},
      {"as3", "briefcase_3", "as3_access_space"},
      {"as4", "briefcase_4", "as4_access_space"},
  };
  return data;
}

const std::vector<tijcore::ModelTraySharedAccessSpaceDescription> &
SceneConfigReader::getListOfSharedAccessSpaceDescriptions() const {
  static const std::vector<tijcore::ModelTraySharedAccessSpaceDescription> data{
      {"agv12_access_space",
       tijcore::RelativePose3{
           world_frame_id_,
           tijcore::Position::fromVector(-2.286283, 3.0, 1.35),
           {}},
       1.2, 4, 2.7},
      {"agv34_access_space",
       tijcore::RelativePose3{
           world_frame_id_,
           tijcore::Position::fromVector(-2.286283, -3.0, 1.35),
           {}},
       1.2, 4, 2.7},

      {"as1_access_space",
       tijcore::RelativePose3{
           "briefcase_1", tijcore::Position::fromVector(0.0, 0.0, 0.0), {}},
       0.6, 0.6, 0.3},
      {"as2_access_space",
       tijcore::RelativePose3{
           "briefcase_2", tijcore::Position::fromVector(0.0, 0.0, 0.0), {}},
       0.6, 0.6, 0.3},
      {"as3_access_space",
       tijcore::RelativePose3{
           "briefcase_3", tijcore::Position::fromVector(0.0, 0.0, 0.0), {}},
       0.6, 0.6, 0.3},
      {"as4_access_space",
       tijcore::RelativePose3{
           "briefcase_4", tijcore::Position::fromVector(0.0, 0.0, 0.0), {}},
       0.6, 0.6, 0.3},

  };
  return data;
}

const std::vector<tijcore::RelativePose3> &
SceneConfigReader::getListOfGantryPlanningHints() const {
  static const std::vector<tijcore::RelativePose3> data{
      {world_frame_id_, tijcore::Position::fromVector(-3.0, 3.1, 0),
       tijcore::Rotation::fromRollPitchYaw(0.0, 0.0, degreesToRadians(-45))},
      {world_frame_id_, tijcore::Position::fromVector(-3.0, 2.9, 0),
       tijcore::Rotation::fromRollPitchYaw(0.0, 0.0, degreesToRadians(-125))},
      // ---
      {world_frame_id_, tijcore::Position::fromVector(-3.0, -2.9, 0),
       tijcore::Rotation::fromRollPitchYaw(0.0, 0.0, degreesToRadians(-45))},
      {world_frame_id_, tijcore::Position::fromVector(-3.0, -3.0, 0),
       tijcore::Rotation::fromRollPitchYaw(0.0, 0.0, degreesToRadians(-125))},
      // ---
      {world_frame_id_, tijcore::Position::fromVector(-5, 3.0, 0),
       tijcore::Rotation::fromRollPitchYaw(0.0, 0.0, degreesToRadians(90))},
      {world_frame_id_, tijcore::Position::fromVector(-5, -3.0, 0),
       tijcore::Rotation::fromRollPitchYaw(0.0, 0.0, degreesToRadians(90))},
      {world_frame_id_, tijcore::Position::fromVector(-10, 3.0, 0),
       tijcore::Rotation::fromRollPitchYaw(0.0, 0.0, degreesToRadians(90))},
      {world_frame_id_, tijcore::Position::fromVector(-10, -3.0, 0),
       tijcore::Rotation::fromRollPitchYaw(0.0, 0.0, degreesToRadians(90))},

  };
  return data;
}

const std::vector<tijcore::RelativePose3> &
SceneConfigReader::getListOfSafeWaitingSpotHints() const {
  static const std::vector<tijcore::RelativePose3> data{
      {world_frame_id_, tijcore::Position::fromVector(-4.0, 3.1, 0),
       tijcore::Rotation::fromRollPitchYaw(0.0, 0.0, degreesToRadians(-5))},
      {world_frame_id_, tijcore::Position::fromVector(-4.0, 2.9, 0),
       tijcore::Rotation::fromRollPitchYaw(0.0, 0.0, degreesToRadians(-175))},
      {world_frame_id_, tijcore::Position::fromVector(-4.0, -3.1, 0),
       tijcore::Rotation::fromRollPitchYaw(0.0, 0.0, degreesToRadians(-175))},
      {world_frame_id_, tijcore::Position::fromVector(-4.0, -2.9, 0),
       tijcore::Rotation::fromRollPitchYaw(0.0, 0.0, degreesToRadians(-5))},
      // ---
      {world_frame_id_, tijcore::Position::fromVector(-5, 3.0, 0),
       tijcore::Rotation::fromRollPitchYaw(0.0, 0.0, degreesToRadians(90))},
      {world_frame_id_, tijcore::Position::fromVector(-5, -3.0, 0),
       tijcore::Rotation::fromRollPitchYaw(0.0, 0.0, degreesToRadians(90))},
      {world_frame_id_, tijcore::Position::fromVector(-10, 3.0, 0),
       tijcore::Rotation::fromRollPitchYaw(0.0, 0.0, degreesToRadians(90))},
      {world_frame_id_, tijcore::Position::fromVector(-10, -3.0, 0),
       tijcore::Rotation::fromRollPitchYaw(0.0, 0.0, degreesToRadians(90))},
  };
  return data;
}

} // namespace tijchallenger