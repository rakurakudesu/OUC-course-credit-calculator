#include <stdio.h>
#include <stdlib.h>  // 用于动态分配内存

// 定义一个结构体来存储每门课程的信息
typedef struct {
    int limit;      // 限选人数
    int selected;   // 已选人数
    float importance; // 课程的重要性
    float ratio;    // 超选比
    float course_coin; // 选课币数量
} Course;

// 计算超选比
void calculateRatio(Course* course) {
    // 超选比公式：r_i = (已选人数 - 限选人数) / 限选人数
    if (course->selected > course->limit) {
        course->ratio = (float)(course->selected - course->limit) / course->limit;
    }
    else {
        course->ratio = 0.0; // 如果没有超选，超选比为0
    }
}

// 计算每门课程的基本分配值
float calculateS(Course* course) {
    return course->importance * (1 + course->ratio);
}

// 计算总的基本分配值总和
float calculateTotalS(Course* courses, int num_courses) {
    float totalS = 0;
    for (int i = 0; i < num_courses; i++) {
        totalS += calculateS(&courses[i]);
    }
    return totalS;
}

// 标准化计算选课币数量
void calculateCourseCoins(Course* courses, float totalS, int num_courses) {
    for (int i = 0; i < num_courses; i++) {
        courses[i].course_coin = (calculateS(&courses[i]) / totalS) * 100;
    }
}

// 输出每门课程的选课币数量
void printCourseCoins(Course* courses, int num_courses) {
    printf("\n课程选课币分配：\n");
    for (int i = 0; i < num_courses; i++) {
        printf("课程 %d - 选课币: %.2f\n", i + 1, courses[i].course_coin);
    }
}

int main() {
    int num_courses;

    // 提示用户输入课程数量
    printf("请输入课程的数量：");
    scanf("%d", &num_courses);

    // 动态分配内存给课程
    Course* courses = (Course*)malloc(num_courses * sizeof(Course));
    if (courses == NULL) {
        printf("内存分配失败！\n");
        return -1;
    }

    // 提示用户输入每门课程的限选人数、已选人数和重要性
    for (int i = 0; i < num_courses; i++) {
        printf("\n请输入课程 %d 的限选人数：", i + 1);
        scanf("%d", &courses[i].limit);
        printf("请输入课程 %d 的已选人数：", i + 1);
        scanf("%d", &courses[i].selected);
        printf("请输入课程 %d 的重要性(0-5)：", i + 1);
        scanf("%f", &courses[i].importance);

        // 计算超选比
        calculateRatio(&courses[i]);
    }

    // 计算总的基本分配值总和
    float totalS = calculateTotalS(courses, num_courses);

    // 计算并输出每门课程的选课币数量
    calculateCourseCoins(courses, totalS, num_courses);
    printCourseCoins(courses, num_courses);

    // 释放分配的内存
    free(courses);

    return 0;
}