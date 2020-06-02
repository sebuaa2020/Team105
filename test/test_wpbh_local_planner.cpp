/*********************************************************************
* Software License Agreement (BSD License)
* 
*  Copyright (c) 2017-2020, Waterplus http://www.6-robot.com
*  All rights reserved.
* 
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
* 
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the WaterPlus nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  FOOTPRINTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/
/*!******************************************************************
 @author     ZhangWanjie
 ********************************************************************/

#include <wpbh_local_planner/wpbh_local_planner.h>
#include <wpbh_local_planner/wl_helper.h>
#include <tf_conversions/tf_eigen.h>
#include <pluginlib/class_list_macros.h>
#include <wpbh_local_planner/CLidarAC.h>

// register this planner as a WpbhLocalPlanner plugin
PLUGINLIB_DECLARE_CLASS(wpbh_local_planner, WpbhLocalPlanner, wpbh_local_planner::WpbhLocalPlanner, nav_core::BaseLocalPlanner)

static CLidarAC lidar_ac;
static float ranges[360];
int test[];

namespace wpbh_local_planner
{
    WpbhLocalPlanner::WpbhLocalPlanner()
    {
        //ROS_WARN("[WPBH]WpbhLocalPlanner() ");
		if (test[1] == 0) {
			printf("***test_wpbh_local_planner 1/58 has done***\n");
		}
		test[1] = test[1] + 1;

        InitHelper();
        m_costmap_ros = NULL;
        m_tf_listener = NULL; 
        m_goal_reached = false;
        m_bInitialized = false;
        m_bAC = false;
        m_bFirstStep = true;
    }

    WpbhLocalPlanner::~WpbhLocalPlanner()
    {
    }

    void WpbhLocalPlanner::initialize(std::string name, tf::TransformListener* tf, costmap_2d::Costmap2DROS* costmap_ros)
    {
		if (test[2] == 0) {
			printf("***test_wpbh_local_planner 2/58 has done***\n");
		}
		test[2] = test[2] + 1;

        ROS_WARN("WpbhLocalPlanner::initialize() ");
        if(!m_bInitialized)
        {	
			if (test[3] == 0) {
				printf("***test_wpbh_local_planner 3/58 has done***\n");
			}
			test[3] = test[3] + 1;

            m_tf_listener = tf;
            m_costmap_ros = costmap_ros;
            m_costmap = m_costmap_ros->getCostmap();
            
            m_global_frame_id = m_costmap_ros->getGlobalFrameID();      //"odom"
            m_robot_base_frame_id = m_costmap_ros->getBaseFrameID();    //"base_footprint"
            
            m_footprint_spec = m_costmap_ros->getRobotFootprint();
            costmap_2d::calculateMinAndMaxDistances(m_footprint_spec, m_robot_inscribed_radius, m_robot_circumscribed_radius); 

            ros::NodeHandle nh_planner("~/" + name);
            nh_planner.param("max_vel_trans", m_max_vel_trans, 0.3);
            nh_planner.param("max_vel_rot", m_max_vel_rot, 0.9);
            nh_planner.param("acc_scale_trans", m_acc_scale_trans, 1.0);
            nh_planner.param("acc_scale_rot", m_acc_scale_rot, 0.5);
            nh_planner.param("goal_dist_tolerance", m_goal_dist_tolerance, 0.1);
            nh_planner.param("goal_yaw_tolerance", m_goal_yaw_tolerance, 0.1);
            nh_planner.param("scan_topic", m_scan_topic, std::string("/scan"));

            m_pub_target = nh_planner.advertise<geometry_msgs::PoseStamped>("local_planner_target", 10);
            m_scan_sub = nh_planner.subscribe<sensor_msgs::LaserScan>(m_scan_topic,1,&WpbhLocalPlanner::lidarCallback,this);
            
            m_bInitialized = true;

            ROS_DEBUG("wpbh_local_planner plugin initialized.");
        }
        else
        {
			if (test[4] == 0) {
				printf("***test_wpbh_local_planner 4/58 has done***\n");
			}
			test[4] = test[4] + 1;

            ROS_WARN("wpbh_local_planner has already been initialized, doing nothing.");
        }
    }

    static double fScaleD2R = 3.14159 / 180;
    void WpbhLocalPlanner::lidarCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
    {
		if (test[5] == 0) {
			printf("***test_wpbh_local_planner 5/58 has done***\n");
		}
		test[5] = test[5] + 1;

        for(int i=0;i<360;i++)
        {
            ranges[i] = scan->ranges[i];
        }
    }

    bool WpbhLocalPlanner::setPlan(const std::vector<geometry_msgs::PoseStamped>& plan)
    {
		if (test[6] == 0) {
			printf("***test_wpbh_local_planner 6/58 has done***\n");
		}
		test[6] = test[6] + 1;

        if(!m_bInitialized)
        {
			if (test[7] == 0) {
				printf("***test_wpbh_local_planner 7/58 has done***\n");
			}
			test[7] = test[7] + 1;

            ROS_ERROR("wpbh_local_planner has not been initialized, please call initialize() before using this planner");
            return false;
        }

        for(int i=0;i<360;i++)
        {
            ranges[i] = 0;
        }

        m_global_plan.clear();
        m_global_plan = plan;
        m_nPathIndex = 0;

        m_goal_reached = false;
        m_nStep = WPBH_STEP_GOTO;
        m_bFirstStep = true;
        
        return true;
    }

    static double CalDirectAngle(double inFromX, double inFromY, double inToX, double inToY)
    {
		if (test[8] == 0) {
			printf("***test_wpbh_local_planner 8/58 has done***\n");
		}
		test[8] = test[8] + 1;

        double res = 0;
        double dx = inFromX - inToX;
        double dy = -(inFromY - inToY);
        if (dx == 0)
        {
			if (test[9] == 0) {
				printf("***test_wpbh_local_planner 9/58 has done***\n");
			}
			test[9] = test[9] + 1;

            if (dy > 0)
            {
				if (test[10] == 0) {
					printf("***test_wpbh_local_planner 10/58 has done***\n");
				}
				test[10] = test[10] + 1;

                res = 180 - 90;
            }
            else
            {
				if (test[11] == 0) {
					printf("***test_wpbh_local_planner 11/58 has done***\n");
				}
				test[11] = test[11] + 1;

                res = 0 - 90;
            }
        }
        else
        {
			if (test[12] == 0) {
				printf("***test_wpbh_local_planner 12/58 has done***\n");
			}
			test[12] = test[12] + 1;

            double fTan = dy / dx;
            res = atan(fTan) * 180 / 3.1415926;

            if (dx < 0)
            {
				if (test[13] == 0) {
					printf("***test_wpbh_local_planner 13/58 has done***\n");
				}
				test[13] = test[13] + 1;

                res = res - 180;
            }
        }
        res = 180 - res;
        if (res < 0)
        {
			if (test[14] == 0) {
				printf("***test_wpbh_local_planner 14/58 has done***\n");
			}
			test[14] = test[14] + 1;

            res += 360;
        }
        if (res > 360)
        {
			if (test[15] == 0) {
				printf("***test_wpbh_local_planner 15/58 has done***\n");
			}
			test[15] = test[15] + 1;

            res -= 360;
        }
        res = res*3.1415926/180;
        return res;
    }

    static double AngleFix(double inAngle, double inMin, double inMax)
    {
		if (test[16] == 0) {
			printf("***test_wpbh_local_planner 16/58 has done***\n");
		}
		test[16] = test[16] + 1;

        if (inMax - inMin > 6.28)
        {
			if (test[17] == 0) {
				printf("***test_wpbh_local_planner 17/58 has done***\n");
			}
			test[17] = test[17] + 1;

            return inAngle;
        }
        
        double retAngle = inAngle;
        while (retAngle < inMin)
        {
			if (test[18] == 0) {
				printf("***test_wpbh_local_planner 18/58 has done***\n");
			}
			test[18] = test[18] + 1;

            retAngle += 6.28;
        }
        while (retAngle > inMax)
        {
			if (test[19] == 0) {
				printf("***test_wpbh_local_planner 19/58 has done***\n");
			}
			test[19] = test[19] + 1;

            retAngle -= 6.28;
        }
        return retAngle;
    }

    bool WpbhLocalPlanner::computeVelocityCommands(geometry_msgs::Twist& cmd_vel)
    {
		if (test[20] == 0) {
			printf("***test_wpbh_local_planner 20/58 has done***\n");
		}
		test[20] = test[20] + 1;

        if(!m_bInitialized)
        {
			if (test[21] == 0) {
				printf("***test_wpbh_local_planner 21/58 has done***\n");
			}
			test[21] = test[21] + 1;

            ROS_ERROR("wpbh_local_planner has not been initialized, please call initialize() before using this planner");
            return false;
        }

        int path_num = m_global_plan.size();
        if(path_num == 0)
        {
			if (test[22] == 0) {
				printf("***test_wpbh_local_planner 22/58 has done***\n");
			}
			test[22] = test[22] + 1;


            return false;
        }

        cmd_vel.linear.x = 0;
        cmd_vel.linear.y = 0;
        cmd_vel.angular.z = 0;
        bool res = true;

        if(m_bFirstStep == true)
        {
			if (test[23] == 0) {
				printf("***test_wpbh_local_planner 23/58 has done***\n");
			}
			test[23] = test[23] + 1;

            double target_x, target_y, target_th;
            while(m_nPathIndex < path_num-1)
            {
				if (test[24] == 0) {
					printf("***test_wpbh_local_planner 24/58 has done***\n");
				}
				test[24] = test[24] + 1;


                getTransformedPosition(m_global_plan[m_nPathIndex], m_robot_base_frame_id, target_x, target_y, target_th);
                if(sqrt(target_x*target_x + target_y*target_y) < m_goal_dist_tolerance)
                {
					if (test[25] == 0) {
						printf("***test_wpbh_local_planner 25/58 has done***\n");
					}
					test[25] = test[25] + 1;

                    m_nPathIndex ++;
                }
                else
                {
					if (test[26] == 0) {
						printf("***test_wpbh_local_planner 26/58 has done***\n");
					}
					test[26] = test[26] + 1;

                    break;  //target is far enough
                }
            }

            double face_target = CalDirectAngle(0, 0, target_x, target_y);
            face_target = AngleFix(face_target,-2.1,2.1);
            if(fabs(face_target)> 0.09)
            {
				if (test[27] == 0) {
					printf("***test_wpbh_local_planner 27/58 has done***\n");
				}
				test[27] = test[27] + 1;

                //turn in place
                cmd_vel.linear.x = 0;
                cmd_vel.linear.y = 0;
                cmd_vel.angular.z = face_target * m_acc_scale_rot;
				if (cmd_vel.angular.z > 0) {
					if (test[28] == 0) {
						printf("***test_wpbh_local_planner 28/58 has done***\n");
					}
					test[28] = test[28] + 1;

					cmd_vel.angular.z += 0.2;
				}
				if (cmd_vel.angular.z < 0) {
					if (test[29] == 0) {
						printf("***test_wpbh_local_planner 29/58 has done***\n");
					}
					test[29] = test[29] + 1;

					cmd_vel.angular.z -= 0.2;
				}
            }
            else
            {
				if (test[30] == 0) {
					printf("***test_wpbh_local_planner 30/58 has done***\n");
				}
				test[30] = test[30] + 1;

                m_bFirstStep = false;
            }
        }
        
        if(m_nStep == WPBH_STEP_ARRIVED)
        {
			if (test[31] == 0) {
				printf("***test_wpbh_local_planner 31/58 has done***\n");
			}
			test[31] = test[31] + 1;

            ROS_WARN("[WPBH_ARRIVED](%.2f %.2f):%.2f",cmd_vel.linear.x,cmd_vel.linear.y,cmd_vel.angular.z);
            return true;
        }

        double goal_x,goal_y,goal_th;
        getTransformedPosition(m_global_plan.back(), m_robot_base_frame_id, goal_x, goal_y, goal_th);
        
        if(m_nStep == WPBH_STEP_GOTO)
        {
			if (test[32] == 0) {
				printf("***test_wpbh_local_planner 32/58 has done***\n");
			}
			test[32] = test[32] + 1;

            lidar_ac.SetRanges(ranges);
            // check if global goal is near
            double goal_dist = sqrt(goal_x*goal_x + goal_y*goal_y);
            if(goal_dist < m_goal_dist_tolerance)
            {
				if (test[33] == 0) {
					printf("***test_wpbh_local_planner 33/58 has done***\n");
				}
				test[33] = test[33] + 1;

                m_nStep = WPBH_STEP_NEAR;
            }
            else
            {
				if (test[34] == 0) {
					printf("***test_wpbh_local_planner 34/58 has done***\n");
				}
				test[34] = test[34] + 1;

                ClearObst();
                SetRanges(ranges);
                //check if target is near
                double target_x, target_y, target_th;
                int path_index = m_nPathIndex;
                while(m_nPathIndex < path_num-1)
                {
					if (test[35] == 0) {
						printf("***test_wpbh_local_planner 35/58 has done***\n");
					}
					test[35] = test[35] + 1;

                    getTransformedPosition(m_global_plan[m_nPathIndex], m_robot_base_frame_id, target_x, target_y, target_th);
                    if((sqrt(target_x*target_x + target_y*target_y) < m_goal_dist_tolerance) || (ChkTarget(target_y/0.05+50,target_x/0.05+50) == false))
                    {
						if (test[36] == 0) {
							printf("***test_wpbh_local_planner 36/58 has done***\n");
						}
						test[36] = test[36] + 1;

                        m_nPathIndex ++;
                    }
                    else
                    {
						if (test[37] == 0) {
							printf("***test_wpbh_local_planner 37/58 has done***\n");
						}
						test[37] = test[37] + 1;

                        break;  //target is far enough
                    }
                }
                
                double gpath_x, gpath_y, gpath_th;
                ClearTarget();
                for(int i=m_nPathIndex;i<path_num;i++)
                {
                    getTransformedPosition(m_global_plan[i], m_robot_base_frame_id, gpath_x, gpath_y, gpath_th);
                    SetTarget(gpath_y/0.05+50,gpath_x/0.05+50);
                }
                res = OutLine();
                if(res == false)
                {
					if (test[38] == 0) {
						printf("***test_wpbh_local_planner 38/58 has done***\n");
					}
					test[38] = test[38] + 1;

                    cmd_vel.linear.x = 0;
                    cmd_vel.linear.y = 0;
                    cmd_vel.angular.z = 0;
                    return true;
                }
                if(GetHelperNum() > 5 && (path_num - m_nPathIndex) > 1)
                {
					if (test[39] == 0) {
						printf("***test_wpbh_local_planner 39/58 has done***\n");
					}
					test[39] = test[39] + 1;

                    target_x = GetFixX();
                    target_y = GetFixY();;
                }
                else
                {
					if (test[40] == 0) {
						printf("***test_wpbh_local_planner 40/58 has done***\n");
					}
					test[40] = test[40] + 1;

                    getTransformedPosition(m_global_plan[m_nPathIndex], m_robot_base_frame_id, target_x, target_y, target_th);
                }
 
                getTransformedPosition(m_global_plan[m_nPathIndex], m_robot_base_frame_id, gpath_x, gpath_y, gpath_th);
                double face_target = CalDirectAngle(0, 0, gpath_x, gpath_y);
                face_target = AngleFix(face_target,-2.1,2.1);
                if(fabs(face_target)> 0.8)
                {
					if (test[41] == 0) {
						printf("***test_wpbh_local_planner 41/58 has done***\n");
					}
					test[41] = test[41] + 1;

                    //turn in place
                    cmd_vel.linear.x = 0;
                    cmd_vel.linear.y = 0;
                    cmd_vel.angular.z = face_target * m_acc_scale_rot;
					if (cmd_vel.angular.z > 0) {
						if (test[42] == 0) {
							printf("***test_wpbh_local_planner 42/58 has done***\n");
						}
						test[42] = test[42] + 1;

						cmd_vel.angular.z += 0.2;
					}
					if (cmd_vel.angular.z < 0) { 
						if (test[43] == 0) {
							printf("***test_wpbh_local_planner 43/58 has done***\n");
						}
						test[43] = test[43] + 1;

						cmd_vel.angular.z -= 0.2;
					}
                }
                else
                {
					if (test[44] == 0) {
						printf("***test_wpbh_local_planner 44/58 has done***\n");
					}
					test[44] = test[44] + 1;

                    // start to move
                    cmd_vel.linear.x = target_x * m_acc_scale_trans;
                    cmd_vel.linear.y = target_y * m_acc_scale_trans;
                    cmd_vel.angular.z = face_target * m_acc_scale_rot;
                  
					if (cmd_vel.linear.x > 0) {
						if (test[45] == 0) {
							printf("***test_wpbh_local_planner 45/58 has done***\n");
						}
						test[45] = test[45] + 1;

						cmd_vel.linear.x += 0.05;
					}
					if (cmd_vel.linear.x < 0) {
						if (test[46] == 0) {
							printf("***test_wpbh_local_planner 46/58 has done***\n");
						}
						test[46] = test[46] + 1;

						cmd_vel.linear.x -= 0.05;
					}
					if (cmd_vel.linear.y > 0) {
						if (test[47] == 0) {
							printf("***test_wpbh_local_planner 47/58 has done***\n");
						}
						test[47] = test[47] + 1;

						cmd_vel.linear.y += 0.02;
					}
					if (cmd_vel.linear.y < 0) {
						if (test[48] == 0) {
							printf("***test_wpbh_local_planner 48/58 has done***\n");
						}
						test[48] = test[48] + 1;

						cmd_vel.linear.y -= 0.02;
					}

                }
                lidar_ac.OutLine();
                m_pub_target.publish(m_global_plan[m_nPathIndex]);
            }
        }

        if(m_nStep == WPBH_STEP_NEAR)
        {
			if (test[49] == 0) {
				printf("***test_wpbh_local_planner 49/58 has done***\n");
			}
			test[49] = test[49] + 1;

            cmd_vel.linear.x = 0;
            cmd_vel.linear.y = 0;
            cmd_vel.angular.z = goal_th;

            if(fabs(goal_th) < m_goal_yaw_tolerance)
            {
				if (test[50] == 0) {
					printf("***test_wpbh_local_planner 50/58 has done***\n");
				}
				test[50] = test[50] + 1;

                m_goal_reached = true;
                m_nStep = WPBH_STEP_ARRIVED;
                cmd_vel.angular.z = 0;
                //ROS_WARN("[WPBH-ARRIVED] goal (%.2f,%.2f) %.2f",goal_x, goal_y, goal_th);
            }
            m_pub_target.publish(m_global_plan.back());
        }

		if (cmd_vel.linear.x > m_max_vel_trans) {
			if (test[51] == 0) {
				printf("***test_wpbh_local_planner 51/58 has done***\n");
			}
			test[51] = test[51] + 1;

			cmd_vel.linear.x = m_max_vel_trans;
		}
		if (cmd_vel.linear.x < -m_max_vel_trans) {
			if (test[52] == 0) {
				printf("***test_wpbh_local_planner 52/58 has done***\n");
			}
			test[52] = test[52] + 1;

			cmd_vel.linear.x = -m_max_vel_trans;
		}
		if (cmd_vel.linear.y > m_max_vel_trans) {
			if (test[53] == 0) {
				printf("***test_wpbh_local_planner 53/58 has done***\n");
			}
			test[53] = test[53] + 1;

			cmd_vel.linear.y = m_max_vel_trans;
		}
		if (cmd_vel.linear.y < -m_max_vel_trans) {
			if (test[54] == 0) {
				printf("***test_wpbh_local_planner 54/58 has done***\n");
			}
			test[54] = test[54] + 1;

			cmd_vel.linear.y = -m_max_vel_trans;
		}
		if (cmd_vel.angular.z > m_max_vel_rot) {
			if (test[55] == 0) {
				printf("***test_wpbh_local_planner 55/58 has done***\n");
			}
			test[55] = test[55] + 1;

			cmd_vel.angular.z = m_max_vel_rot;
		}
		if (cmd_vel.angular.z < -m_max_vel_rot) {
			if (test[56] == 0) {
				printf("***test_wpbh_local_planner 56/58 has done***\n");
			}
			test[56] = test[56] + 1;

			cmd_vel.angular.z = -m_max_vel_rot;
		}

        m_last_cmd = cmd_vel;
        
        return res;
    }


    bool WpbhLocalPlanner::isGoalReached()
    {
        if (m_goal_reached)
        {
			if (test[57] == 0) {
				printf("***test_wpbh_local_planner 57/58 has done***\n");
			}
			test[57] = test[57] + 1;

            ROS_INFO("GOAL Reached!");
            return true;
        }
        return false;
    }

    void WpbhLocalPlanner::getTransformedPosition(geometry_msgs::PoseStamped& pose, std::string& frame_id, double& x, double& y, double& theta)
    {
		if (test[58] == 0) {
			printf("***test_wpbh_local_planner 58/58 has done***\n");
		}
		test[58] = test[58] + 1;

        geometry_msgs::PoseStamped tf_pose;
        pose.header.stamp = ros::Time(0);
        m_tf_listener->transformPose(frame_id, pose, tf_pose);
        x = tf_pose.pose.position.x;
        y = tf_pose.pose.position.y,
        theta = tf::getYaw(tf_pose.pose.orientation);
    }

}