/**
 * Husky Control through Terminal
 * 
 * Here lies the instructions that will show up in terminal
 * Visit https://github.com/MURDriverless/HuskyControl for latest version and instructions on how to use
 * 
 * Current Version by Kheng Yu Yeoh, contact @ khengyu_061192@hotmail.com 
 */

#include <stdlib.h>
#include "terminalcontrol.h"
#include <vector>

/* Function List */
bool instruction(TerminalControlHusky& husky, ros::Rate rate);

int main(int argc, char **argv)
{
    // Initialize ROS node
    ros::init(argc, argv, "husky_terminal_controller");

    // Get parameters from CLI
    double max_v = atof(argv[1]);
    double max_w = atof(argv[2]);
    double lingain = atof(argv[3]);
    double anggain = atof(argv[4]);
    
    //Initialize Husky Object
    TerminalControlHusky husky = TerminalControlHusky(max_v, max_w, lingain, anggain);

    // Husky takes commands at 50Hz
    ros::Rate rate(50);

    while(ros::ok()) // while ros is running, repeat this 
    {
        if(instruction(husky, rate))
        {
            // exit is run, exit program
            return 0;
        }

        ros::spinOnce();
    }
}

// Instructions for main()
// Prompts for user input to determine commands
bool instruction(TerminalControlHusky& husky, ros::Rate rate)
{
    // Initialize Variables
    int command;
    double dist, speed, angle;
    bool isForward;

    // Ask for command
    std::cout << "Hello, this program has these listed functions. Please enter the command.\n";
    std::cout << "1) Specify movement and direction to Husky.\n";
    std::cout << "2) Specify location for Husky to travel to.\n";
    std::cout << "3) To test Husky movements by rotating in place.\n";
    std::cout << "4) To test Husky movements by moving forwards and backward.\n";
    std::cout << "5) Input Path Points for Husky to follow (x,y)\n";
    std::cout << "0) What is Husky's current Position and Orientation?\n";
    std::cout << "Any other number => Exit\n";
    while(!(std::cin >> command))
    {
        std::cout << "You have entered a wrong input, please only specify numbers. ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    if (command == 1)
    {
        std::cout << "What is the distance? ";
        while(!(std::cin >> dist))
        {
            std::cout << "You have entered a wrong input, please specify distance with numbers only.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "What is the distance? ";
        }
        std::cout << "What is the speed (m/s) to travel at? ";
        while(!(std::cin >> speed))
        {
            std::cout << "You have entered a wrong input, please specify speed with numbers only.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "What is the speed (m/s) to travel at? ";
        }
        std::cout << "Are you moving forwards? Answer 1 for true or 0 for false. ";
        while(!(std::cin >> isForward))
        {
            std::cout << "You have entered a wrong input, please specify 1 or 0.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Are you moving forwards? Answer 1 for true or 0 for false. ";
        }
        std::cout << "How many degrees to the left would you like to turn? ";
        while(!(std::cin >> angle))
        {
            std::cout << "You have entered a wrong input, please specify a number\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "How many degrees to the left would you like to turn? ";
        }

        husky.move(dist, speed, isForward, angle*M_PI/180);

        return 0;
    }
    
    else if(command == 2)
    {
        // Update Position
        ros::spinOnce();
        
        // Initialize Variables
        double goto_x, goto_y, error;

        std::cout << "Current pose of Husky is\n";
        std::cout << "x: " << husky.getX() << "\n";
        std::cout << "y: " << husky.getY() << "\n";
        std::cout << "angle: " << husky.getPhi()*180/M_PI << "\n";
        std::cout << "Where would you like the Husky to go to?\n";
        std::cout << "x = ";
        while(!(std::cin >> goto_x))
        {
            std::cout << "You have entered a wrong input, please specify with numbers only.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "x = ";
        }
        std::cout << "y = ";
        while(!(std::cin >> goto_y))
        {
            std::cout << "You have entered a wrong input, please specify with numbers only.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "y = ";
        }
        std::cout << "error threshold = ";
        while(!(std::cin >> error))
        {
            std::cout << "You have entered a wrong input, please specify with numbers only.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "error = ";
        }

        husky.smoothMove(goto_x, goto_y, error);

        return 0;
    }

    else if(command == 3)
    {
        int rotTimeTest;
        std::cout << "Would you like to try rotating using time based approach? Answer 1 for true or 0 for false. ";
        while(!(std::cin >> rotTimeTest))
        {
            std::cout << "You have entered a wrong input, please specify 1 or 0.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Would you like to try rotating using time based approach? Answer 1 for true or 0 for false. ";
        }
        if(rotTimeTest)
        {
            husky.testRotTime();
        }

        int rotTest;    
        std::cout << "Would you like to try rotating using feedback control? Answer 1 for true or 0 for false. ";
        while(!(std::cin >> rotTest))
        {
            std::cout << "You have entered a wrong input, please specify 1 or 0.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Would you like to try rotating using feedback control? Answer 1 for true or 0 for false. ";
        }
        if(rotTest)
        {
            husky.testRot();
        }

        return 0;
    }

    else if(command == 4)
    {
        int moveTimeTest;
        std::cout << "Would you like to try moving using time based approach? Answer 1 for true or 0 for false. ";
        while(!(std::cin >> moveTimeTest))
        {
            std::cout << "You have entered a wrong input, please specify 1 or 0.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Would you like to try moving using time based approach? Answer 1 for true or 0 for false. ";
        }
        if(moveTimeTest)
        {
            husky.testMoveTime();
        }

        int moveTest;    
        std::cout << "Would you like to try moving using feedback control? Answer 1 for true or 0 for false. ";
        while(!(std::cin >> moveTest))
        {
            std::cout << "You have entered a wrong input, please specify 1 or 0.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Would you like to try moving using feedback control? Answer 1 for true or 0 for false. ";
        }
        if(moveTest)
        {
            husky.testMove();
        }

        return 0;
    }

    else if (command == 5)
    {
        std::vector<float> x,y;
        x.reserve(20);
        y.reserve(20);
        ros::spinOnce();
        std::cout << "Current pos of Husky is: (";
        std::cout << husky.getX()<<", "<<husky.getY()<< ")"<<std::endl;

        int numPoints = 1;
        float temp;
        char yn;
        while(true)
        {
            std::cout << "\nEnter path point "<<numPoints<< ". x= ";
            while(!(std::cin >> temp))
            {
                std::cout << "You have entered a wrong input, please specify x coordinate with numbers only.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout <<  "\nEnter point "<<numPoints<< ". x= ";
            }
            x.push_back(temp);
            std::cout << "Enter point "<<numPoints<< ". y= ";
            while(!(std::cin >> temp))
            {
                std::cout << "You have entered a wrong input, please specify y coordinate with numbers only.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout <<  "Enter path point "<<numPoints<< ". y= ";
            }
            y.push_back(temp);
            std::cout << "Add more path points? y/n ";
            while(!(std::cin >> yn))
            {
                std::cout << "You have entered a wrong input,'y' or 'n' only.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Add more path points? y/n ";
            }
            if (yn == 'y')
            {
                numPoints ++;
                std::cout<<"path points entered: ";
                for (int i=0;i<x.size();i++)
                {
                    std::cout<<"("<<x[i]<<", "<<y[i]<<") ";
                }

            }
            else if(yn == 'n')
            {
                std::cout<<"path points entered: ";
                for (int i=0;i<x.size();i++)
                {
                    std::cout<<"("<<x[i]<<", "<<y[i]<<") ";
                }
                break;
            }

        }
        std::cout<<"path points size: "<<x.size()<<std::endl;
        husky.pathFollower(x,y);
        return 0;
    }

    else if(command == 0)
    {
        // Update Position
        ros::spinOnce();

        std::cout << "Current pose of Husky is\n";
        std::cout << "x: " << husky.getX() << "\n";
        std::cout << "y: " << husky.getY() << "\n";
        std::cout << "angle: " << husky.getPhi()*180/M_PI << "\n";

        return 0;
    }

    else // entered random number, exit
    {
        std::cout << "Exiting program...";
        return 1;
    }
}