#include <stdio.h>
#define max 5

// int a[11] = { 10, 14, 19, 26, 27, 31, 33, 35, 42, 44, 0 };
int a[5] = { 10, 27, 19, 26, 14,};
int b[5];

void merging(int low, int mid, int high) {
      int l1, l2, i;

   for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
      if(a[l1] <= a[l2]){
         b[i] = a[l1++];
          printf("%d %d %d ", a[l1], a[l2], b[i]);
      } else {
         b[i] = a[l2++];
         printf("%d %d ", a[l2], b[i]);
      }
   }

   while(l1 <= mid) {
      b[i++] = a[l1++];
      printf("%d %d ", a[l1], b[i]);
   }

   while(l2 <= high){
      b[i++] = a[l2++];
      // printf("%d ", b[i]);
   }

   for(i = low; i <= high; i++){
      a[i] = b[i];
      printf("\n33. %d %d ", a[i], b[i]);
   }
}

void sort(int low, int high) {
   int mid;
  // printf("%d ", mid);

   if(low < high) {
      mid = (low + high) / 2;
      printf("\n%d %d %d ", low, mid, high);
      sort(low, mid);
      sort(mid+1, high);
       printf("\n46. %d %d %d ", low, mid, high);
      merging(low, mid, high);
   } else {
      return;
   }
}

int main() {
   int i;

   printf("List before sorting\n");

   for(i = 0; i <= max; i++)
      printf("%d ", a[i]);

   sort(0, max);

   printf("\nList after sorting\n");

   for(i = 0; i <= max; i++)
      printf("%d ", a[i]);
}