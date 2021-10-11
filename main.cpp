//DMITRIY GRUSHIN [OPERATING SYSTEMS]

#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <ctime>

using namespace std;

// returns a string of the day of the week given a number
string dayOfWeekToString(int day) {
    switch (day){
        case 0: 
            return "Sunday";
            break;
        case 1:
            return "Monday";
            break;
        case 2: 
            return "Tuesday"; 
            break;
        case 3: 
            return "Wednesday"; 
            break;
        case 4:
            return "Thursday"; 
            break;
        case 5: 
            return "Friday";
            break;
        case 6: 
            return "Saturday"; 
            break;
        default: 
            return "NOT A WEEKDAY";
    }
}

int main()
{
    pid_t c_pid = fork(); 
    
    // allows you to get the current date
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int month =  ltm->tm_mon + 1;
    int day = ltm->tm_mday;
    int year = 1900 + ltm->tm_year;
    int dayOfWeek = ltm->tm_wday;
    
    if (c_pid == -1) { // error during fork()
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (c_pid > 0) { // parent process
        cout << "--------------------------------------------------------" << endl;
        cout << "PARENT: process - [PID:" << getpid() << "]" << endl;
        cout << "\t Date: " << month << "-" << day << "-" << year << endl; 
        wait(nullptr); // parent waits until child process has finished.
    } else { // child process
        cout << "--------------------------------------------------------" << endl;
        cout << "CHILD: process - [PID:" << getpid() << "]"<< endl;
        cout << "\tDay Of Week: " << dayOfWeekToString(dayOfWeek) << endl;
        cout << "\tPARENT'S - [PID: " << getppid() << "]" << endl;
        exit(EXIT_SUCCESS);
    }

    return EXIT_SUCCESS;
}

/*OUTPUT:
--------------------------------------------------------
PARENT: process - [PID:1039]
	 Date: 9-25-2021
--------------------------------------------------------
CHILD: process - [PID:1043]
	Day Of Week: Saturday
	PARENT'S - [PID: 1039]
*/