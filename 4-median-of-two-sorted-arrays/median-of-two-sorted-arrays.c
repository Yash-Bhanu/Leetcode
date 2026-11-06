#include <limits.h>

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    if (nums1Size > nums2Size) {
        return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);
    }

    int low = 0;
    int high = nums1Size;
    int halfLen = (nums1Size + nums2Size + 1) / 2;

    while (low <= high) {
        int cut1 = (low + high) / 2;
        int cut2 = halfLen - cut1;

        int left1, right1, left2, right2;
        if (cut1 == 0) {
            left1 = INT_MIN;
        } else {
            left1 = nums1[cut1 - 1];
        }

        if (cut1 == nums1Size) {
            right1 = INT_MAX;
        } else {
            right1 = nums1[cut1];
        }
        if (cut2 == 0) {
            left2 = INT_MIN;
        } else {
            left2 = nums2[cut2 - 1];
        }

        if (cut2 == nums2Size) {
            right2 = INT_MAX;
        } else {
            right2 = nums2[cut2];
        }
        if (left1 <= right2 && left2 <= right1) {
       
            int maxLeft;
            if (left1 > left2) {
                maxLeft = left1;
            } else {
                maxLeft = left2;
            }
            if ((nums1Size + nums2Size) % 2 == 1) {
                return (double)maxLeft;
            }
            int minRight;
            if (right1 < right2) {
                minRight = right1;
            } else {
                minRight = right2;
            }

            return (maxLeft + minRight) / 2.0;
        } 
        else if (left1 > right2) {
          
            high = cut1 - 1;
        } 
        else {
          
            low = cut1 + 1;
        }
    }

    return 0.0;
}