#include <stdio.h>
#include <iostream>
#include <ros/ros.h>
#include <string>  
#include <vector>  
#include <fstream>
#include <sstream>
#include "mur_common/path_msg.h"

#define PATH_TOPIC "/mur/planner/path"

//std::string fileName;

mur_common::path_msg spin(std::vector<float> &x, std::vector<float> &y)
{
    if (ros::ok())
        ros::spinOnce();
    
    //publish path
    mur_common::path_msg msg;
    msg.header.frame_id = "map";
    msg.x = x;
    msg.y = y;

    return msg;

}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "pathNodes");
    ros:: NodeHandle n;

    //n.getParam("path_file",fileName);



    ros::Publisher pub_path;
    pub_path = n.advertise<mur_common::path_msg>(PATH_TOPIC,1);
    ROS_INFO_STREAM("Path publisher launched!");

//this part reads and sorts the csv file 
    std::string line;
    std::string temp;
    std::vector<float> nums;
    float num;
    int h = 0;
    std::vector<float> x,y;
    x.reserve(500);
    y.reserve(500);
    nums.reserve(1000);
    std::ifstream myFile;
    myFile.open("path0.csv");
    while (!myFile.eof())
    {
        
        std::getline(myFile,line,'\n');
        std::cout<<" "<<std::endl;
    
        for (auto c:line)
        {
            if (c == 't')
            {
                temp.clear();
                break; //skip first line
            }
                
            if (c == ',')
            {
                h++; //comma counter
                if (temp.size() == 0)
                    ;//first
                else
                {
                    num = std::stof(temp);
                    nums.push_back(num);
                    temp.clear();
                }
            }   
            else if (c=='m' || c=='a' || c=='p')
                nums.clear();
            else
                temp.push_back(c);
        }
        nums.push_back(num);

       // std::cout<<"commas: " << h << "\n\n nums size: "<<nums.size()<< std::endl;
        
        int sz = nums.size()/3;
        for(int i=0; i<sz;i++)
        {
            x.push_back(nums[i]);
            y.push_back(nums[i+sz]);
        }

        for (int i = 0; i <x.size();i++)
        {
            std::cout<<"x,y = "<<x[i]<<","<<y[i]<<std::endl;
        }

        //publish
        mur_common::path_msg msg = spin(x,y);
        pub_path.publish(msg);
        ros::Duration(0.05).sleep();

        //clear vectors
        x.clear();
        y.clear();
        nums.clear();
        line.clear();
    }
    myFile.close();

    
 
}
