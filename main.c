#include <stdio.h>

void solution1_run(int num_readers, int num_writers, double *avg_reader_tat, double *avg_writer_tat);
void solution2_run(int num_readers, int num_writers, double *avg_reader_tat, double *avg_writer_tat);
void solution3_run(int num_readers, int num_writers, double *avg_reader_tat, double *avg_writer_tat);

int main() {
    int num_readers = 10;

    printf("Readers-Writers Solution 1 (time in seconds)\n");
    printf("Writers AVG reader TAT AVG writer TAT AVG TAT\n");
    for (int num_writers = 0; num_writers <= 10; num_writers++) {
        double avg_reader_tat = 0;
        double avg_writer_tat = 0;
        solution1_run(num_readers, num_writers, &avg_reader_tat, &avg_writer_tat);
        double avg_tat;
        if (num_writers == 0) {
            avg_tat = avg_reader_tat;
            printf("%d %lf N/A %lf\n", num_writers, avg_reader_tat, avg_tat);
        } else {
            avg_tat = (avg_reader_tat * num_readers + avg_writer_tat * num_writers) / (num_readers + num_writers);
            printf("%d %lf %lf %lf\n", num_writers, avg_reader_tat, avg_writer_tat, avg_tat);
        }
    }

    printf("Readers-Writers Solution 2 (time in seconds)\n");
    printf("Writers AVG reader TAT AVG writer TAT AVG TAT\n");
    for (int num_writers = 0; num_writers <= 10; num_writers++) {
        double avg_reader_tat = 0;
        double avg_writer_tat = 0;
        solution2_run(num_readers, num_writers, &avg_reader_tat, &avg_writer_tat);
        double avg_tat;
        if (num_writers == 0) {
            avg_tat = avg_reader_tat;
            printf("%d %lf N/A %lf\n", num_writers, avg_reader_tat, avg_tat);
        } else {
            avg_tat = (avg_reader_tat * num_readers + avg_writer_tat * num_writers) / (num_readers + num_writers);
            printf("%d %lf %lf %lf\n", num_writers, avg_reader_tat, avg_writer_tat, avg_tat);
        }
    }

    printf("Readers-Writers Solution 3 (time in seconds)\n");
    printf("Writers AVG reader TAT AVG writer TAT AVG TAT\n");
    for (int num_writers = 0; num_writers <= 10; num_writers++) {
        double avg_reader_tat = 0;
        double avg_writer_tat = 0;
        solution3_run(num_readers, num_writers, &avg_reader_tat, &avg_writer_tat);
        double avg_tat;
        if (num_writers == 0) {
            avg_tat = avg_reader_tat;
            printf("%d %lf N/A %lf\n", num_writers, avg_reader_tat, avg_tat);
        } else {
            avg_tat = (avg_reader_tat * num_readers + avg_writer_tat * num_writers) / (num_readers + num_writers);
            printf("%d %lf %lf %lf\n", num_writers, avg_reader_tat, avg_writer_tat, avg_tat);
        }
    }

    return 0;
}