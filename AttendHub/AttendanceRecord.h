//#pragma once
#ifndef ATTENDANCERECORD_H
#define ATTENDANCERECORD_H

#include <iostream>
#include <vector>
#include <string>

class AttendanceRecord {
public:
    static void viewAllAttendance(const std::string& _class);
    static void viewAttendanceOfStudent(const std::string& scholarID);
    static void editAttendance(const std::string& _class);
    static void addAttendance(const std::string& _class);
};

#endif

