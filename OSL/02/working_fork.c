#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

void bubble(int arr[], int n){
	int temp;
	for(int i = 0; i<n-1; i++){
		for(int j = 0; j<n-i-1; j++){
			if(arr[j] > arr[j+1]){
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}

void merge(int arr[], int left, int mid, int right){
	int n1 = mid - left + 1;
	int n2 = right - mid;

	int L[n1], R[n2];

	for(int i =0; i<n1; i++){
		L[i] = arr[left + i];
	}

	for(int i = 0; i<n2; i++){
		R[i] = arr[mid+1+i];
	}

	int i=0,j=0, k = left;

	while(i<n1 && j<n2){
		if(L[i]<=R[j]){
			arr[k++]=L[i++];
		}
		else{
			arr[k++]=R[j++];
		}
	}

	while (i<n1)
	{
		arr[k++] = L[i++];
	}
	while(j<n2){
		arr[k++] = R[j++];
	}
	
}

void mergeSort(int arr[], int left, int right){
	if(left<right){
		int mid = left + (right - left) /2;
		mergeSort(arr, left, mid);
		mergeSort(arr, mid+1, right);

		merge(arr, left, mid, right);
	}
}

int main(){

	int arr[5] = {5, 2 ,3, 8, 1};
	mergeSort(arr, 0, 4);
	for(int i =0 ;i<5; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0;
}