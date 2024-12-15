#include <stdio.h>
#include <stdlib.h>  // ���ڶ�̬�����ڴ�

// ����һ���ṹ�����洢ÿ�ſγ̵���Ϣ
typedef struct {
    int limit;      // ��ѡ����
    int selected;   // ��ѡ����
    float importance; // �γ̵���Ҫ��
    float ratio;    // ��ѡ��
    float course_coin; // ѡ�α�����
} Course;

// ���㳬ѡ��
void calculateRatio(Course* course) {
    // ��ѡ�ȹ�ʽ��r_i = (��ѡ���� - ��ѡ����) / ��ѡ����
    if (course->selected > course->limit) {
        course->ratio = (float)(course->selected - course->limit) / course->limit;
    }
    else {
        course->ratio = 0.0; // ���û�г�ѡ����ѡ��Ϊ0
    }
}

// ����ÿ�ſγ̵Ļ�������ֵ
float calculateS(Course* course) {
    return course->importance * (1 + course->ratio);
}

// �����ܵĻ�������ֵ�ܺ�
float calculateTotalS(Course* courses, int num_courses) {
    float totalS = 0;
    for (int i = 0; i < num_courses; i++) {
        totalS += calculateS(&courses[i]);
    }
    return totalS;
}

// ��׼������ѡ�α�����
void calculateCourseCoins(Course* courses, float totalS, int num_courses) {
    for (int i = 0; i < num_courses; i++) {
        courses[i].course_coin = (calculateS(&courses[i]) / totalS) * 100;
    }
}

// ���ÿ�ſγ̵�ѡ�α�����
void printCourseCoins(Course* courses, int num_courses) {
    printf("\n�γ�ѡ�αҷ��䣺\n");
    for (int i = 0; i < num_courses; i++) {
        printf("�γ� %d - ѡ�α�: %.2f\n", i + 1, courses[i].course_coin);
    }
}

int main() {
    int num_courses;

    // ��ʾ�û�����γ�����
    printf("������γ̵�������");
    scanf("%d", &num_courses);

    // ��̬�����ڴ���γ�
    Course* courses = (Course*)malloc(num_courses * sizeof(Course));
    if (courses == NULL) {
        printf("�ڴ����ʧ�ܣ�\n");
        return -1;
    }

    // ��ʾ�û�����ÿ�ſγ̵���ѡ��������ѡ��������Ҫ��
    for (int i = 0; i < num_courses; i++) {
        printf("\n������γ� %d ����ѡ������", i + 1);
        scanf("%d", &courses[i].limit);
        printf("������γ� %d ����ѡ������", i + 1);
        scanf("%d", &courses[i].selected);
        printf("������γ� %d ����Ҫ��(0-5)��", i + 1);
        scanf("%f", &courses[i].importance);

        // ���㳬ѡ��
        calculateRatio(&courses[i]);
    }

    // �����ܵĻ�������ֵ�ܺ�
    float totalS = calculateTotalS(courses, num_courses);

    // ���㲢���ÿ�ſγ̵�ѡ�α�����
    calculateCourseCoins(courses, totalS, num_courses);
    printCourseCoins(courses, num_courses);

    // �ͷŷ�����ڴ�
    free(courses);

    return 0;
}