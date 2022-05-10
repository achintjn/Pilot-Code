/*
* Name: Achint Jain
* G-Number - G01324710
*
* Note: I have commented some output console to just see the running time, please uncomment/comment as per the need.
* */


import java.util.Random;

public class AnalyseSorting {

    public static void insertionSortAsc(int [] arr)
    {
        int length = arr.length;
        for(int i=1;i<length;i++){
            int left_key = arr[i];
            int j = i -1;

            while(j>=0 && arr[j]>left_key){
                arr[j+1] = arr[j];
                j = j-1;
            }
            arr[j+1] = left_key;
        }
    }

    public static void insertionSortDesc(int [] arr)
    {
        int length = arr.length;
        for(int i=1;i<length;i++){
            int left_key = arr[i];
            int j = i -1;

            while(j>=0 && arr[j]<left_key){
                arr[j+1] = arr[j];
                j = j-1;
            }
            arr[j+1] = left_key;
        }
    }

    public static void selectionSortAsc(int [] arr) {

        int index;
        int temp;

        for (int i = 0; i < arr.length - 1; i++) {
            index = i;
            for (int j = i+1; j < arr.length ; j++) {
                if (arr[j] < arr[index]){
                    index = j;
                }}

            temp = arr[i];
            arr[i] = arr[index];
            arr[index] = temp;
            }
        }

    /*public static void selectionSortDesc(int [] arr) {

        int index;
        int temp;

        for (int i = 0; i < arr.length - 1; i++) {
            index = i;
            for (int j = i+1; j < arr.length ; j++) {
                if (arr[j] > arr[index]){
                    index = j;
                }}

            temp = arr[i];
            arr[i] = arr[index];
            arr[index] = temp;
        }
    }*/


    public static void inputOne(Random rd){

        for(int j=5000; j<=30000; j = j +5000) {             //this loop will run for n=5000,10000,15000,...

            int[] arr = new int[j];
            int[] arr2 = new int[j];

            int k = 0;
            long total =0;
            long total2 =0;

            while(k<3){                                     //this loop will run for 3 times with different random data and calculate the average.
                for (int i = 0; i < arr.length; i++) {      //another loop to generate random value from 1 to n
                    arr[i] = rd.nextInt(j) +1;              //+1 to eliminate 0 from the array and include nth value
                    arr2[i] = arr[i];
                    //System.out.println("not sorted " + arr[i]);  // printing each array element, uncomment to view the values
                }

                long start = System.nanoTime();
                insertionSortAsc(arr);
                long end = System.nanoTime();
                long timeElapsed = end - start;             //calculating time in nanoseconds for insertion sort

                for(int arr1:arr)
                    System.out.println("sorted for Insertion sort: "+arr1);   //comment to hide the sorted list


                long start2 = System.nanoTime();
                selectionSortAsc(arr2);
                long end2 = System.nanoTime();
                long timeElapsed2 = end2 - start2;          //calculating time in nanoseconds for selection sort

                for(int arrSel:arr2)
                    System.out.println("sorted for Selection sort: "+arrSel);   //comment to hide the sorted list


                total = total + timeElapsed;

                total2 = total2 + timeElapsed2;

                //System.out.println("Execution time in milliseconds: " + timeElapsed);
                k++;
            }

            total = total/3;
            total2 = total2/3;

            System.out.println("INPUT1: Average time for Insertion Sort and Selection Sort for n = "+j+" is: "+total+" , "+total2);

            //System.out.println("/n");
            //System.out.println( total+" , "+total2);      //output in csv format to easily convert in excel formatt.
        }
    }

    public static void inputTwo(Random rd){

        for(int j=5000; j<=30000; j = j + 5000) {
            int[] arr = new int[j];

            int k = 0;
            //float total =0;

                for (int i = 0; i < arr.length; i++) {
                    arr[i] = rd.nextInt(j) +1;          // storing random integers in an array
                    //System.out.println("not sorted " + arr[i]);   // printing each array element
                }

            insertionSortAsc(arr);                      // generating non-decreasing inputs
                long start1 = System.nanoTime();
                insertionSortAsc(arr);
                long end1 = System.nanoTime();
                long timeElapsed1 = end1 - start1;

              for(int arr1:arr)
                    System.out.println("sorted insertion sort: "+arr1);

                long start = System.nanoTime();
                selectionSortAsc(arr);
                long end = System.nanoTime();
                long timeElapsed = end - start;

                for(int arr1:arr)
                    System.out.println("sorted selection sort: "+arr1);


                System.out.println("INPUT2: Execution time for insertion and selection sort in nano for n="+ j+" : " + timeElapsed1+" , "+timeElapsed);


            //System.out.println( total+" , "+total2);      //output in csv format to easily convert in excel formatt.
        }

    }

    private static void inputThree(Random rd) {

        for(int j=5000; j<=30000; j = j + 5000) {
            int[] arr = new int[j];

            int k = 0;
            //float total =0;

            for (int i = 0; i < arr.length; i++) {
                arr[i] = rd.nextInt(j) +1; // storing random integers in an array
                //System.out.println("not sorted " + arr[i]); // printing each array element
            }

            insertionSortDesc(arr);
            long start1 = System.nanoTime();
            insertionSortAsc(arr);
            long end1 = System.nanoTime();
            long timeElapsed1 = end1 - start1;
            for(int arr1:arr)
                    System.out.println("sorted insertion sort: "+arr1);      //comment to just see the time

            insertionSortDesc(arr);
            long start = System.nanoTime();
            selectionSortAsc(arr);
            long end = System.nanoTime();
            long timeElapsed = end - start;

                for(int arr1:arr)
                    System.out.println("sorted for selection sort: "+arr1);  //Comment to just see the time


            System.out.println("INPUT3: Execution time for insertion and selection sort in nano for n="+ j+" : " + timeElapsed1+" , "+timeElapsed);


            //System.out.println( total+" , "+total2);      //output in csv format to easily convert in excel formatt.
        }
    }

    private static void inputFour(Random rd) {
        for(int j=5000; j<=30000; j = j + 5000) {
            int[] arr = new int[j];
            int[] arr2 = new int[j];

            int k = 0;
            long total =0;
            long total2 = 0;
            while(k<3) {                //this loop will run for 3 times ot take the average of each run with random input
                for (int i = 0; i < arr.length; i++) {
                    arr[i] = rd.nextInt(j) +1; //+1 to exclude 0 and include any n
                    arr2[i] = arr[i];// storing random integers in an array
                    //System.out.println("not sorted " + arr[i]); // printing each array element
                }

                insertionSortAsc(arr);    //reusing insertion sort like plot 2
                insertionSortAsc(arr2);  //reusing insertion sort like plot 2

                int repeat50 = 0;
                while (repeat50 < 50) {   //running 50 time to excange xi and xj
                    int r1 = rd.nextInt(j);     //index for x1
                    int r2 = rd.nextInt(j);     //index for xj

                    int temp = arr[r1];
                    arr[r1] = arr[r2];
                    arr[r2] = temp;

                    int temp2 = arr2[r1];
                    arr2[r1] = arr2[r2];
                    arr2[r2] = temp2;

                    repeat50++;
                }

                long start = System.nanoTime();
                insertionSortAsc(arr);
                long end = System.nanoTime();
                long timeElapsed = end - start;


                for(int arr1:arr)
                    System.out.println("sorted for insertion sort: "+arr1);    //uncomment to view th sorted list

                long start2 = System.nanoTime();
                selectionSortAsc(arr2);
                long end2 = System.nanoTime();
                long timeElapsed2 = end2 - start2;

                for(int arr1:arr2)
                    System.out.println("sorted for selection sort: "+arr1);  //uncomment to view the sorted list

                total = total + timeElapsed;
                total2 = total2 + timeElapsed2;
                total = total/3;
                total2 = total2/3;

                k++;
            }
            System.out.println("INPUT4: Execution time for insertion and selection sort in nano for n="+ j+" : " + total+" , "+total2);
        }

        //System.out.println( total+" , "+total2);      //output in csv format to easily convert in excel formatt.
    }

    public static void inputFive(Random rd) {

        //System.out.println("hello");
        int [] arr = new int[50];
        int [] arr2 = new int[50];
        long total_runtime = 0;
        long total_runtime2 = 0;
        for(int i=0;i<100000;i++){  //loop for generating 100,000 random inputs

            for (int j = 0; j < arr.length; j++) {  //loop for generating 50 random array input
                arr[j] = rd.nextInt(50) +1;
                arr2[j] = arr[j];// storing random integers in an array
                //System.out.println("not sorted " + arr[i]); // printing each array element
            }

            long start = System.nanoTime();
            insertionSortAsc(arr);
            long end = System.nanoTime();
            long timeElapsed = end - start;

            for(int arr1:arr)
                    System.out.println("sorted for insertion sort: "+arr1);    //uncomment to view th sorted list

            long start2 = System.nanoTime();
            selectionSortAsc(arr2);
            long end2 = System.nanoTime();
            long timeElapsed2 = end2 - start2;

            for(int arr1:arr2)
                    System.out.println("sorted for selection sort: "+arr1);  //uncomment to view the sorted list

            total_runtime = total_runtime + timeElapsed;
            total_runtime2 = total_runtime2 + timeElapsed2;

        }

        System.out.println("INPUT5: Execution time for Insertion and Selection sort in nano: " + total_runtime+" , "+total_runtime2);

        //System.out.println( total+" , "+total2);      //output in csv format to easily convert in excel formatt.
    }


    public static void main(String[] args) {



        Random rd = new Random(); // creating a Random object

        //comment each method to see individual result
        inputOne(rd);
        System.out.println(" ");
        inputTwo(rd);
        System.out.println(" ");
        inputThree(rd);
        System.out.println(" ");
        inputFour(rd);
        System.out.println(" ");
        inputFive(rd);
    }
}
