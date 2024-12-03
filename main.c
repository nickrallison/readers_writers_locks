#include <stdio.h>
#include <stdlib.h>

void solution1_run(int num_readers, int num_writers, double **avg_reader_tat, double **avg_writer_tat);
void solution2_run(int num_readers, int num_writers, double **avg_reader_tat, double **avg_writer_tat);
void solution3_run(int num_readers, int num_writers, double **avg_reader_tat, double **avg_writer_tat);

int main() {
    int num_readers = 10;

    printf("Readers-Writers Solution 1 (time in seconds)\n");
    printf("%-8s %-15s %-15s %-15s\n", "Writers", "AVG reader TAT", "AVG writer TAT", "AVG TAT");
    for (int num_writers = 0; num_writers <= 10; num_writers++) {
        double reader_time_by_id[num_readers];
        double writer_time_by_id[num_writers];
        solution1_run(num_readers, num_writers, &reader_time_by_id, &writer_time_by_id);
        double total_reader_time = 0;
        double total_writer_time = 0;
        for (int i = 0; i < num_readers; i++) {
            total_reader_time += reader_time_by_id[i];
        }
        for (int i = 0; i < num_writers; i++) {
            total_writer_time += writer_time_by_id[i];
        }
        double avg_reader_tat = (num_readers > 0) ? total_reader_time / num_readers : 0;
        double avg_writer_tat = (num_writers > 0) ? total_writer_time / num_writers : 0;

        double avg_tat;
        if (num_writers == 0) {
            avg_tat = avg_reader_tat;
            printf("%-8d %-15.6lf %-15s %-15.6lf\n", num_writers, avg_reader_tat, "N/A", avg_tat);
        } else {
            avg_tat = (avg_reader_tat * num_readers + avg_writer_tat * num_writers) / (num_readers + num_writers);
            printf("%-8d %-15.6lf %-15.6lf %-15.6lf\n", num_writers, avg_reader_tat, avg_writer_tat, avg_tat);
        }
    }

    printf("Readers-Writers Solution 2 (time in seconds)\n");
    printf("%-8s %-15s %-15s %-15s\n", "Writers", "AVG reader TAT", "AVG writer TAT", "AVG TAT");
    for (int num_writers = 0; num_writers <= 10; num_writers++) {
        double reader_time_by_id[num_readers];
        double writer_time_by_id[num_writers];
        for (int i = 0; i < num_readers; i++) {
            reader_time_by_id[i] = 0;
        }
        for (int i = 0; i < num_writers; i++) {
            writer_time_by_id[i] = 0;
        }
        solution2_run(num_readers, num_writers, &reader_time_by_id, &writer_time_by_id);
        double total_reader_time = 0;
        double total_writer_time = 0;
        for (int i = 0; i < num_readers; i++) {
            total_reader_time += reader_time_by_id[i];
        }
        for (int i = 0; i < num_writers; i++) {
            total_writer_time += writer_time_by_id[i];
        }
        double avg_reader_tat = (num_readers > 0) ? total_reader_time / num_readers : 0;
        double avg_writer_tat = (num_writers > 0) ? total_writer_time / num_writers : 0;

        double avg_tat;
        if (num_writers == 0) {
            avg_tat = avg_reader_tat;
            printf("%-8d %-15.6lf %-15s %-15.6lf\n", num_writers, avg_reader_tat, "N/A", avg_tat);
        } else {
            avg_tat = (avg_reader_tat * num_readers + avg_writer_tat * num_writers) / (num_readers + num_writers);
            printf("%-8d %-15.6lf %-15.6lf %-15.6lf\n", num_writers, avg_reader_tat, avg_writer_tat, avg_tat);
        }
    }

    printf("Readers-Writers Solution 3 (time in seconds)\n");
    printf("%-8s %-15s %-15s %-15s\n", "Writers", "AVG reader TAT", "AVG writer TAT", "AVG TAT");
    for (int num_writers = 0; num_writers <= 10; num_writers++) {
        double reader_time_by_id[num_readers];
        double writer_time_by_id[num_writers];
        solution3_run(num_readers, num_writers, &reader_time_by_id, &writer_time_by_id);
        double total_reader_time = 0;
        double total_writer_time = 0;
        for (int i = 0; i < num_readers; i++) {
            total_reader_time += reader_time_by_id[i];
        }
        for (int i = 0; i < num_writers; i++) {
            total_writer_time += writer_time_by_id[i];
        }
        double avg_reader_tat = (num_readers > 0) ? total_reader_time / num_readers : 0;
        double avg_writer_tat = (num_writers > 0) ? total_writer_time / num_writers : 0;

        double avg_tat;
        if (num_writers == 0) {
            avg_tat = avg_reader_tat;
            printf("%-8d %-15.6lf %-15s %-15.6lf\n", num_writers, avg_reader_tat, "N/A", avg_tat);
        } else {
            avg_tat = (avg_reader_tat * num_readers + avg_writer_tat * num_writers) / (num_readers + num_writers);
            printf("%-8d %-15.6lf %-15.6lf %-15.6lf\n", num_writers, avg_reader_tat, avg_writer_tat, avg_tat);
        }
    }

    return 0;
}