// -*- C++ -*-
/*!
 * @file  ARTKMarkerInfoToPose2D.cpp
 * @brief Convert ARTKMarkerInfoSeq data to Pose2D
 * @date $Date$
 *
 * $Id$
 */

#include "ARTKMarkerInfoToPose2D.h"

// Module specification
// <rtc-template block="module_spec">
static const char* artkmarkerinfotopose2d_spec[] =
  {
    "implementation_id", "ARTKMarkerInfoToPose2D",
    "type_name",         "ARTKMarkerInfoToPose2D",
    "description",       "Convert ARTKMarkerInfoSeq data to Pose2D",
    "version",           "1.0.0",
    "vendor",            "ota",
    "category",          "DataTypeConver",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.pose1_id", "0",
    "conf.default.pose2_id", "68",
    "conf.default.pose3_id", "1",
    "conf.default.adjust_x", "0.0",
    "conf.default.adjust_y", "0.0",
    "conf.default.adjust_angle", "0.0",

    // Widget
    "conf.__widget__.pose1_id", "text",
    "conf.__widget__.pose2_id", "text",
    "conf.__widget__.pose3_id", "text",
    "conf.__widget__.adjust_x", "text",
    "conf.__widget__.adjust_y", "text",
    "conf.__widget__.adjust_angle", "text",
    // Constraints

    "conf.__type__.pose1_id", "int",
    "conf.__type__.pose2_id", "int",
    "conf.__type__.pose3_id", "int",
    "conf.__type__.adjust_x", "double",
    "conf.__type__.adjust_y", "double",
    "conf.__type__.adjust_angle", "double",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
ARTKMarkerInfoToPose2D::ARTKMarkerInfoToPose2D(RTC::Manager* manager)
// <rtc-template block="initializer">
: RTC::DataFlowComponentBase(manager),
m_marker_infoIn("maker_info", m_marker_info),
m_pose1Out("pose1", m_pose1),
m_pose2Out("pose2", m_pose2),
m_pose3Out("pose3", m_pose3)

// </rtc-template>
{
}

/*!
 * @brief destructor
 */
ARTKMarkerInfoToPose2D::~ARTKMarkerInfoToPose2D()
{
}



RTC::ReturnCode_t ARTKMarkerInfoToPose2D::onInitialize()
{
	// Registration: InPort/OutPort/Service
	// <rtc-template block="registration">
	// Set InPort buffers
	addInPort("maker_info", m_marker_infoIn);

	// Set OutPort buffer
	addOutPort("pose1", m_pose1Out);
	addOutPort("pose2", m_pose2Out);
	addOutPort("pose3", m_pose3Out);

	// Set service provider to Ports

	// Set service consumers to Ports

	// Set CORBA Service Ports

	// </rtc-template>

	// <rtc-template block="bind_config">
	// Bind variables and configuration variable
	bindParameter("pose1_id", m_pose1_id, "0");
	bindParameter("pose2_id", m_pose2_id, "68");
	bindParameter("pose3_id", m_pose3_id, "1");
	bindParameter("adjust_x", m_adjust_x, "0.0");
	bindParameter("adjust_y", m_adjust_y, "0.0");
	bindParameter("adjust_angle", m_adjust_angle, "0.0");
	// </rtc-template>

	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ARTKMarkerInfoToPose2D::onFinalize()
{
return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ARTKMarkerInfoToPose2D::onStartup(RTC::UniqueId ec_id)
{
return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ARTKMarkerInfoToPose2D::onShutdown(RTC::UniqueId ec_id)
{
return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t ARTKMarkerInfoToPose2D::onActivated(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}


RTC::ReturnCode_t ARTKMarkerInfoToPose2D::onDeactivated(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}


RTC::ReturnCode_t ARTKMarkerInfoToPose2D::onExecute(RTC::UniqueId ec_id)
{
	if (m_marker_infoIn.isNew()){
		//printf("Data_ok\n");
		m_marker_infoIn.read();

		for (int i = 0; i < m_marker_info.length(); i++) {
			if (m_marker_info[i].id == m_pose1_id){
				m_pose1.data.position.x = -m_marker_info[i].markerPoseMatrix[1][3] + m_adjust_x;
				m_pose1.data.position.y = m_marker_info[i].markerPoseMatrix[2][3] + m_adjust_y;
				m_pose1.data.heading = atan2(m_marker_info[i].markerPoseMatrix[2][1],
					m_marker_info[i].markerPoseMatrix[2][2]) * 180 / 3.14159; // + m_adjust_angle;
				if (m_pose1.data.heading < 0 || m_pose1.data.heading + m_adjust_angle < 0){
					m_pose1.data.heading += 360 + m_adjust_angle;
				}
				else{
					m_pose1.data.heading += m_adjust_angle;
				}
			}
			else if (m_marker_info[i].id == m_pose2_id){
				m_pose2.data.position.x = -m_marker_info[i].markerPoseMatrix[1][3] + m_adjust_x;
				m_pose2.data.position.y = m_marker_info[i].markerPoseMatrix[2][3] + m_adjust_y;
				m_pose2.data.heading = atan2(m_marker_info[i].markerPoseMatrix[2][1],
					m_marker_info[i].markerPoseMatrix[2][2]) * 180 / 3.14159; // + m_adjust_angle;
				if (m_pose2.data.heading < 0 || m_pose2.data.heading + m_adjust_angle < 0){
					m_pose2.data.heading += 360 + m_adjust_angle;
				}
				else{
					m_pose2.data.heading += m_adjust_angle;
				}
			}
			std::cout << "   position.x,   position.y,   heading " << std::endl;
			std::cout << "pose1: " << m_pose1.data.position.x << ",  " << m_pose1.data.position.y << ",  " << m_pose1.data.heading << std::endl;
			std::cout << "pose2: " << m_pose2.data.position.x << ",  " << m_pose2.data.position.y << ",  " << m_pose2.data.heading << std::endl;
			std::cout << "\n";
		}
		m_pose1Out.write();
		m_pose2Out.write();
	}
	return RTC::RTC_OK;
}


/*
RTC::ReturnCode_t ARTKMarkerInfoToPose2D::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ARTKMarkerInfoToPose2D::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ARTKMarkerInfoToPose2D::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ARTKMarkerInfoToPose2D::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ARTKMarkerInfoToPose2D::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void ARTKMarkerInfoToPose2DInit(RTC::Manager* manager)
  {
    coil::Properties profile(artkmarkerinfotopose2d_spec);
    manager->registerFactory(profile,
                             RTC::Create<ARTKMarkerInfoToPose2D>,
                             RTC::Delete<ARTKMarkerInfoToPose2D>);
  }
  
};


