#ifndef ROSINTERFACE_H
#define ROSINTERFACE_H

#include "ros/ros.h"
#include "../CaptainInterFace/CaptainInterFace.h"

#include "captain_interface/scientistmsg.h"

#ifndef PI 
#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286
#endif

//Ros messages
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Header.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/TwistWithCovarianceStamped.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/QuaternionStamped.h>
#include <sensor_msgs/FluidPressure.h>
#include <sensor_msgs/MagneticField.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/NavSatFix.h>
#include <geographic_msgs/GeoPoint.h>
#include <geographic_msgs/GeoPointStamped.h>
#include <smarc_msgs/DVL.h>
#include <smarc_msgs/FloatStamped.h>
#include <smarc_msgs/ThrusterRPM.h>
#include <smarc_msgs/ThrusterFeedback.h>
#include <smarc_msgs/Leak.h>
#include <lolo_msgs/CaptainStatus.h>
//#include <lolo_msgs/VbsValves.h>
//#include <lolo_msgs/VbsTank.h>

struct RosInterFace {

  //================== ROS Nodehandle ====================//
  ros::NodeHandle* n;
  CaptainInterFace* captain;

  void init(ros::NodeHandle* nh, CaptainInterFace* cap);

  //======================================================//
  //================== ROS subscribers ===================//
  //======================================================//

  //TODO
  // USBL/RF/etc

  //information / other things
  ros::Subscriber heartbeat_sub;        //heartbeat message
  ros::Subscriber done_sub;             //scientist mission completed
  ros::Subscriber abort_sub;            //abort

  //Control commands: High level
  ros::Subscriber waypoint_sub;         //target waypoint
  ros::Subscriber waypoint_sub_UTM;     //target waypoint UTM
  ros::Subscriber speed_sub;            //target speed
  ros::Subscriber depth_sub;            //target depth
  ros::Subscriber altitude_sub;         //target altitude

  //Control commands medium level
  ros::Subscriber yaw_sub;              //target course
  ros::Subscriber yawrate_sub;          //target turn rate
  ros::Subscriber pitch_sub;            //target pitch
  ros::Subscriber rpm_sub;              //target RPM (average if differential thrust is enabled)

  //Control commands low level
  //thrusters
  ros::Subscriber thrusterPort_sub;
  ros::Subscriber thrusterStrb_sub;

  //control surfaces
  ros::Subscriber rudder_sub;
  ros::Subscriber elevator_sub;

  //Lolo onboard console
  ros::Subscriber menu_sub;

  //======================================================//
  //=================== ROS pubishers ====================//
  //======================================================//
  //thrusters
  ros::Publisher thrusterPort_pub;
  ros::Publisher thrusterStrb_pub;

  //constrol surfaces
  ros::Publisher rudder_angle_pub;
  ros::Publisher elevator_angle_pub;
  ros::Publisher elevon_port_angle_pub;
  ros::Publisher elevon_strb_angle_pub;

  //VBS
  ros::Publisher VBS_front_tank_pub;
  ros::Publisher VBS_aft_tank_pub;
  ros::Publisher VBS_valves_pub;
  ros::Publisher VBS_motor_pub;

  //Leak sensors
  ros::Publisher leak_dome;

  //sensors
  ros::Publisher imu_pub;
  ros::Publisher magnetometer_pub;
  ros::Publisher pressure_pub;
  ros::Publisher dvl_pub;
  ros::Publisher gps_pub;
  ros::Publisher fls_pub;

  //control / status
  ros::Publisher status_orientation_pub;
  ros::Publisher status_altitude_pub;
  ros::Publisher status_position_pub;
  ros::Publisher status_depth_pub;
  ros::Publisher status_twist_pub;

  ros::Publisher control_status_pub;
  ros::Publisher vehiclestate_pub;


  //General purpose text output
  ros::Publisher text_pub;

  //Lolo onboard console
  ros::Publisher menu_pub;

  //======================================================//
  //=================== ROS callbacks ====================//
  //======================================================//

  void ros_callback_heartbeat(const std_msgs::Empty::ConstPtr &_msg);
  void ros_callback_abort(const std_msgs::Empty::ConstPtr &_msg);
  void ros_callback_done(const std_msgs::Empty::ConstPtr &_msg);
  //void ros_callback_waypoint(const smarc_msgs::LatLonStamped::ConstPtr &_msg);
  void ros_callback_waypoint(const geographic_msgs::GeoPoint::ConstPtr &_msg);
  void ros_callback_speed(const std_msgs::Float64::ConstPtr &_msg);
  void ros_callback_depth(const std_msgs::Float64::ConstPtr &_msg);
  void ros_callback_altitude(const std_msgs::Float64::ConstPtr &_msg);
  void ros_callback_yaw(const std_msgs::Float64::ConstPtr &_msg);
  void ros_callback_yawrate(const std_msgs::Float64::ConstPtr &_msg);
  void ros_callback_pitch(const std_msgs::Float64::ConstPtr &_msg);
  void ros_callback_rpm(const std_msgs::Float64::ConstPtr &_msg);
  void ros_callback_rudder(const std_msgs::Float64::ConstPtr &_msg);
  void ros_callback_elevator(const std_msgs::Float64::ConstPtr &_msg);
  void ros_callback_thrusterPort(const std_msgs::Float64::ConstPtr &_msg);
  void ros_callback_thrusterStrb(const std_msgs::Float64::ConstPtr &_msg);
  void ros_callback_menu(const std_msgs::String::ConstPtr &_msg);

  //======================================================//
  //================= Captain callbacks ==================//
  //======================================================//

  void captain_callback_LEAK();
  void captain_callback_STATUS();
  void captain_callback_CONTROL();
  void captain_callback_RUDDER();
  void captain_callback_ELEVATOR();
  void captain_callback_ELEVON_PORT();
  void captain_callback_ELEVON_STRB();
  void captain_callback_THRUSTER_PORT();
  void captain_callback_THRUSTER_STRB();
  void captain_callback_BATTERY();
  void captain_callback_DVL();
  void captain_callback_GPS();
  void captain_callback_IMU();
  void captain_callback_MAG();
  void captain_callback_PRESSURE();
  void captain_callback_VBS();
  void captain_callback_POSITION();
  void captain_callback_FLS();
  void captain_callback_TEXT();
  void captain_callback_MENUSTREAM();

  void captain_callback() {
    int msgID = captain->messageID();
    switch (msgID) {
      case CS_LEAK: {         captain_callback_LEAK(); }; break; //Leak
      case CS_STATUS: {       captain_callback_STATUS(); } break; //status
      case CS_CONTROL: {      captain_callback_CONTROL(); } break; //control
      case CS_RUDDER: {       captain_callback_RUDDER(); } break; // rudder
      case CS_ELEVATOR: {     captain_callback_ELEVATOR(); } break; //elevator
      case CS_ELEVON_PORT: {  captain_callback_ELEVON_PORT(); } break; //Port elevon
      case CS_ELEVON_STRB: {  captain_callback_ELEVON_STRB(); } break; //Strb elevon
      case CS_THRUSTER_PORT: {captain_callback_THRUSTER_PORT(); } break; //port thruster
      case CS_THRUSTER_STRB: {captain_callback_THRUSTER_STRB(); } break; //strb thruster
      case CS_BATTERY: {      captain_callback_BATTERY(); } break; //battery
      case CS_DVL: {          captain_callback_DVL(); } break; //DVL
      case CS_GPS: {          captain_callback_GPS(); } break; //GPS
      case CS_IMU: {          captain_callback_IMU(); } break; //IMU
      case CS_MAG: {          captain_callback_MAG(); } break; //MAG
      case CS_PRESSURE: {     captain_callback_PRESSURE();} break; //PRESSURE
      case CS_VBS: {          captain_callback_VBS(); } break; //VBS
      case CS_POSITION: {     captain_callback_POSITION(); } break; //Position
      case CS_FLS: {          captain_callback_FLS(); } break; //FLS
      case CS_TEXT: {         captain_callback_TEXT(); } break;  //General purpose text message
      case CS_MENUSTREAM: {   captain_callback_MENUSTREAM(); } break; //Menu stream data
    };
  };
};

#endif //ROSINTERFACE_H