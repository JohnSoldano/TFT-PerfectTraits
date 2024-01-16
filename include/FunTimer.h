#ifndef FUNTIMER_H
#define FUNTIMER_H

/* 
    [2024/01/16] - Display formatted time eg. HH:MM:SS 
*/ 

#include <ctime>
#include <iostream>

class FunTimer {
    private:
        clock_t time_start;
        clock_t time_end;
        float time_taken;

        // Converts to seconds
        void calculateTimeTaken() { time_taken = float(time_end - time_start)/CLOCKS_PER_SEC; }

    public:
        FunTimer() { }

        // Begin Timer
        void TimeBegin() { time_start = clock(); }

        // Stop Timer
        void TimeEnd() {
            time_end = clock();
            calculateTimeTaken();
        }

        // Display Time Taken
        float GetTimeTaken() { return time_taken; }

        // Display formatted time taken
        void DisplayTimeTaken() {
            std::cout << "Time Taken: " << GetTimeTaken() << std::endl;
        }

};

#endif // FUNTIMER_H