#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_COURSES 33
#define MAX_NAME_LENGTH 100
#define MAX_CODE_LENGTH 10
#define MAX_ENROLLED_COURSES 9
typedef struct courseList {
    int id;
    char code[MAX_CODE_LENGTH];
    char name[MAX_NAME_LENGTH];
    int units;
    char section[4];
    char schedule[50];
    char day[50];
    char room[10];
} Course;
//creating of structures
typedef struct {
    char name[MAX_NAME_LENGTH];
    int units_enrolled;
    Course *enrolled_courses[MAX_COURSES];
    Course *prev_enrolled_courses[MAX_ENROLLED_COURSES];
    int prev_enrolled_count;
    Course *doublePrev_enrolled_courses[100];
} Student;
Course courses[MAX_COURSES];
Student student;
struct courseList initializeCourses[] = { //structure containing courses being offered
    {0, "LCC..09", "Lasallian Core Curriculum", 3,"EA1", "07:30-9:00", "Monday and Thursday", "R101"},
    {1, "LCC..09", "Lasallian Core Curriculum", 3, "EA2", "11:00-12:30", "Monday and Thursday", "R101"},
    {2, "LCC..09", "Lasallian Core Curriculum", 3, "EA3", "15:30-17:00", "Monday and Thursday", "R101"},
    {3, "LCC..09", "Lasallian Core Curriculum", 3, "YK1", "10:00-11:30", "Tuesday and Friday", "R101"},
    {4, "LCC..09", "Lasallian Core Curriculum", 3, "YK2", "13:00-14:30", "Tuesday and Friday", "R101"},
    {5, "LCC..09", "Lasallian Core Curriculum", 3, "YK3", "16:00-17:30", "Tuesday and Friday", "R101"},
 
    {6, "MICPROS", "Microprocessors Lecture", 3, "EA1", "8:30-10:00", "Wednesday and Saturday", "R102"},
    {7, "MICPROS", "Microprocessors Lecture", 3, "EA2", "12:00-13:30", "Wednesday and Saturday", "R102"},
    {8, "MICPROS", "Microprocessors Lecture", 3, "YO2", "15:00-16:30", "Tuesday and Friday", "R102"},
   
    {9, "LBYCPA3", "Microprocessors Laboratory", 1, "UI2", "7:30-10:30", "Monday", "LAB1"},
    {10, "LBYCPA3", "Microprocessors Laboratory", 1, "UI3", "13:00-16:00", "Monday", "LAB1"},
   
    {11, "LBYCPA3", "Microprocessors Laboratory", 1, "UL7", "14:00-17:00", "Friday", "LAB1"},
    {12, "LBYCPA3", "Microprocessors Laboratory", 1, "UL9", "18:00-21:00", "Friday", "LAB1"},
   
    {13, "LBYCPB3", "Computer Engineering Drafting and Design Laboratory", 1, "AK4", "9:15-11:45", "Wednesday", "LAB2"},
    {14, "LBYCPB3", "Computer Engineering Drafting and Design Laboratory", 1, "AU3", "13:45-15:15", "Wednesday", "LAB2"},
    {15, "LBYCPB3", "Computer Engineering Drafting and Design Laboratory", 1, "KL1", "9:15-11:45", "Saturday", "LAB2"},
    {16, "LBYCPB3", "Computer Engineering Drafting and Design Laboratory", 1, "KL2", "13:45-15:15", "Saturday", "LAB2"},
 
    {17, "LBYEC3B", "Intelligent System for Engineering", 1, "CP3", "7:30-9:00", "Tuesday and Friday", "R103"},
    {18, "LBYEC3B", "Intelligent System for Engineering", 1, "OP4", "14:15-15:45", "Tuesday and Friday", "R103"},
    {19, "LBYEC3B", "Intelligent System for Engineering", 1, "OP6", "18:30-20:00", "Tuesday and Friday", "R103"},
 
    {20, "LBYCPF2", "Introduction to HDL Laboratory", 1, "EA1", "12:00-15:00", "Thursday", "LAB3"},
    {21, "LBYCPF2", "Introduction to HDL Laboratory", 1, "EA3", "17:00-12:00", "Thursday", "LAB3"},
 
    {22, "DIGDACM", "Data and Digital Communication", 3, "EA5", "11:45-13:15", "Monday and Thursday", "R104"},
    {23, "DIGDACM", "Data and Digital Communication", 3, "AU3", "15:00-16:30", "Monday and Thursday", "R104"},
    {24, "DIGDACM", "Data and Digital Communication", 3, "OP4", "12:00-13:30", "Tuesday and Friday", "R104"},
    {25, "DIGDACM", "Data and Digital Communication", 3, "YO2", "15:00-16:30", "Tuesday and Friday", "R104"},
 
    {26, "PETHFOUR", "Generic Code", 2, "AK4", "9:00-10:30", "Wednesday and Friday", "PE Center"},
    {27, "PETHFOUR", "Generic Code", 2, "YK2", "13:30-15:00", "Wednesday and Friday", "PE Center"},
    {28, "PETHFOUR", "Generic Code", 2, "UL1", "17:30-19:00", "Wednesday and Friday", "PE Center"},
 
    {29, "LBYCPG2", "Basic Computer System Administration", 1, "AU3", "12:00-15:00", "Wednesday", "R105"},
    {30, "LBYCPG2", "Basic Computer System Administration", 1, "KL2", "14:00-17:00", "Wednesday", "R105"},
    {31, "LBYCPG2", "Basic Computer System Administration", 1, "AU3", "15:00-18:00", "Friday", "R105"},
    {32, "LBYCPG2", "Basic Computer System Administration", 1, "KL2", "14:30-17:30", "Friday", "R105"}
};

//module for initializing student's profile's values
void initializeStudent() {
    strcpy(student.name, "John Doe");
    student.units_enrolled = 0;
    student.prev_enrolled_count = 0;
    for (int i = 0; i < MAX_COURSES; i++) {
        student.enrolled_courses[i] = NULL;
    }
    for (int i = 0; i < MAX_ENROLLED_COURSES; i++) {
        student.prev_enrolled_courses[i] = NULL;
    }
}

//module for displaying available courses
void displayCourses(struct courseList courses[], int size) {
    printf("Available Courses:\n");
    for (int i = 0; i < MAX_COURSES; i++) {
        printf("%-1d %-10s %-100s %-10d %-4s %-50s %-50s %-10s\n", courses[i].id, courses[i].code, courses[i].name, courses[i].units, courses[i].section, courses[i].schedule, courses[i].day, courses[i].room);
    }
}

//For showing enrolled courses
void displayPrevEnrolledCourses() {
    printf("Previously Enrolled Courses for %s:\n", student.name);
    for (int i = 0; i < student.prev_enrolled_count; i++) {
        printf("%-10s %-s\n", student.prev_enrolled_courses[i]->code, student.prev_enrolled_courses[i]->name);
    }
}

//module for detecting interference or conflicting courses
void detector(){
    int interferenceDetected = 0; // Flag to track interference
    for (int i = 0; i < student.prev_enrolled_count; i++){
        for (int j = i + 1; j < student.prev_enrolled_count; j++){
            //detects if enrolled courses are the same
            if (strcmp(student.prev_enrolled_courses[i]->name, student.prev_enrolled_courses[j]->name) == 0){
                printf("Interference detected: Same course name\n");
                interferenceDetected += 1;
                break;
            }//detects if enrolled course have the same time and day with other enrolled courses
            else if (strcmp(student.prev_enrolled_courses[i]->day, student.prev_enrolled_courses[j]->day) == 0 &&
                     strcmp(student.prev_enrolled_courses[i]->schedule, student.prev_enrolled_courses[j]->schedule) == 0){
                printf("Interference detected: Same time and day\n");
                interferenceDetected += 1;
                break;
            }
        }
        if (interferenceDetected) {
            break; // Break outer loop if interference detected
        }
    }
    if (!interferenceDetected) {
        printf("No interference\n");
    }
}

//module for enrolling students 
void enrollStudent(int course_index) {
    
    //checking if the course will exceed maximum number of units
    if (student.units_enrolled + initializeCourses[course_index].units <= 12) {
        student.enrolled_courses[student.units_enrolled] = &initializeCourses[course_index];
 
        if (student.prev_enrolled_count < MAX_ENROLLED_COURSES) {
            student.prev_enrolled_courses[student.prev_enrolled_count++] = &initializeCourses[course_index];
            student.units_enrolled += initializeCourses[course_index].units;
            printf("Enrolled in %-100s successfully!\n", initializeCourses[course_index].name);
        } else {
            printf("You have reached the maximum quantity of courses.");
        }
    } 
    else {
        printf("Cannot enroll in %s. Exceeds maximum units allowed.\n", initializeCourses[course_index].name);
    }
}

//main module
int main() {
    int size = sizeof(initializeCourses) / sizeof(initializeCourses[0]);
    //initializing empty student's profile
    initializeStudent();
 
    int choice;
    do {
        printf("1. Display Available Courses\n");
        printf("2. Enroll Student\n");
        printf("3. Display Previously Enrolled Courses\n");
        printf("4. Check for interfering courses\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice); printf("\n ");
 
        switch (choice) {
            case 1:
                displayCourses(initializeCourses, size);
                break;
            case 2: 
                int course_index;
                printf("Enter course index (0-%d): ", MAX_COURSES - 1);
                scanf("%d", &course_index);
                enrollStudent(course_index);
                break;
            case 3:
                displayPrevEnrolledCourses();
                break;
            case 4:
                detector();
                break;
            case 5: //program will quit if user inputs number 5
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
    return 0;
}
