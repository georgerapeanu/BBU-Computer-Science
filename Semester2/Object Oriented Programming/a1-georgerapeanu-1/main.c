/* Rapeanu George - Alexandru - 916
 * Problem 9.
 * a. Decompose a given natural number in its prime factors.
 * b. Given a vector of numbers, find the longest contiguous subsequence such that any consecutive elements contain the same digits.

 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int size;
    int v[100];
}vector_t;

vector_t decompose(int n){
    /*! This function decomposes a given number into its prime factors.
     *  @param n: the number to pe decompose
     *  @return a vector struct containing the factors
     */

    vector_t factors;
    factors.size = 0;

    int copy_n = n;

    for(int d = 2;1LL * d * d <= n;d++){
        while(n % d == 0) {
            factors.size++;
            n /= d;
        }
    }
    if(n != 1){
        factors.size++;
    }

    n = copy_n;

    factors.size = 0;
    for(int d = 2; 1LL * d * d <= n;d++){
        while(n % d == 0){
            factors.v[factors.size++] = d;
            n /= d;
        }
    }
    if(n != 1){
        factors.v[factors.size++] = n;
    }
    return factors;
}

int same_digits(int a, int b) {
    /*! This function checks that two given numbers have the same digits
     * @param a: the first number
     * @param b: the second number
     * @return 1 if the numbers have the same digits and 0 otherwise
     */
    ///frequency vector that will store for i the frequency of the digit i in a - the frequency of the digit i in b
    vector_t fr;

    for (int i = 0; i < 10; i++) {
        fr.v[i] = 0;
    }

    if (a == 0) {
        fr.v[0]++;
    }
    while (a) {
        fr.v[a % 10]++;
        a /= 10;
    }

    if (b == 0) {
        fr.v[0]--;
    }
    while (b) {
        fr.v[b % 10]--;
        b /= 10;
    }

    int ok = 1;

    for (int i = 0; i < 10; i++) {
        if(fr.v[i] != 0){
            ok = 0;
            break;
        }
    }

    return ok;
}

void longest_subsequence_with_same_digits(vector_t v, int*l, int*r){
    /*! This function calculates the longest subsequence with numbers with the same digits
     * @param v: the vector_t object on which to extract the subsequence
     * @param l: pointer to the int that will receive the left index on the array
     * @param r: pointer to the int that will receive the right index of the array
     * @return nothing
     */

    *l = *r = 0;
    int current_length = 0;

    for(int i = 0;i < v.size;i++){
        if(i == 0 || same_digits(v.v[i - 1], v.v[i]) == 0){
            current_length = 0;
        }
        current_length++;
        if(*r - *l < current_length){
            *r = i + 1; /// the range will be returned as [l,r), so r is i + 1
            *l = i - current_length + 1;
        }
    }
}

vector_t read_vector(){
    /*!This function reads an vector from console
     * @return a vector_t object containing the array
     */
    vector_t v;
    printf("Please enter the size of the array:");
    scanf("%d", &v.size);
    printf("Please enter the array's elements separated by space: ");

    for(int i = 0;i < v.size;i++) {
        scanf("%d", &v.v[i]);
    }
    return v;
}

void print_vector(vector_t v){
    /*! This function writes a given vector
     * @param v: the vector to be printed
     *  @return nothing
     */

    for(int i = 0;i < v.size;i++){
        printf("%d ", v.v[i]);
    }
    printf("\n");
}

void handle_decompose(){
    /*! This function handles the decompose functionality UI
     */
    int n;
    printf("Please enter a number:");
    scanf("%d", &n);
    vector_t factors = decompose(n);
    printf("The factors are:");
    print_vector(factors);
}

void handle_subsequence(){
    /*! This function handles the subsequence functionality UI
    */
    vector_t v = read_vector();
    int l = 0, r = 0;
    longest_subsequence_with_same_digits(v, &l, &r);
    vector_t subsequence;
    subsequence.size = r - l;
    for(int i = 0;i < subsequence.size;i++){
        subsequence.v[i] = v.v[i + l];
    }
    print_vector(subsequence);
}

void display_help(){
    printf("Usage:\n");
    printf("decompose\n");
    printf("\twriting this will prompt you to the first functionality of the app\n");
    printf("\tyou can use it in order to decompose a given number\n");
    printf("longest subsequence\n");
    printf("\twriting this will prompt you to the second functionality of the app\n");
    printf("\tyou can use it in order to see the longest subsequence of numbers which contain the same digits\n");
    printf("help\n");
    printf("\tthis will display the help prompt\n");
    printf("exit\n");
    printf("\tthis stops the application\n");
}

void test_decompose(){
    /*! This function runs some tests for the decompose functionality
     */

    vector_t current_output;
    current_output = decompose(1);
    assert(current_output.size == 0);

    current_output = decompose(10);
    assert(current_output.size == 2);
    assert(current_output.v[0] == 2);
    assert(current_output.v[1] == 5);

    current_output = decompose(3);
    assert(current_output.size == 1);
    assert(current_output.v[0] == 3);

    current_output = decompose(2);
    assert(current_output.size == 1);
    assert(current_output.v[0] == 2);

    current_output = decompose(12412);
    assert(current_output.size == 4);
    assert(current_output.v[0] == 2);
    assert(current_output.v[1] == 2);
    assert(current_output.v[2] == 29);
    assert(current_output.v[3] == 107);
}

void test_subsequence(){
    /*! This function runs some tests for the subsequence functionality
     */
    vector_t input_v;

    input_v.size = 10;
    input_v.v[0] = 1;
    input_v.v[1] = 11;
    input_v.v[2] = 111;
    input_v.v[3] = 211;
    input_v.v[4] = 121;
    input_v.v[5] = 112;
    input_v.v[6] = 211;
    input_v.v[7] = 122;
    input_v.v[8] = 121;
    input_v.v[9] = 212;

    int l = 0;
    int r = 0;
    longest_subsequence_with_same_digits(input_v, &l, &r);

    assert(l == 3);
    assert(r == 7);
}

void run_tests(){
    /*! This function runs some tests for the application
     */
    test_decompose();
    test_subsequence();
    printf("Tests ok\n");
}

int main() {

    run_tests();

    char command[100];

    display_help();
    while(1){
        fgets(command, 100, stdin);
        int n = (int)strlen(command);
        if(command[n - 1] == '\n'){
            command[--n] = 0;
        }
        if(n == 0){
            continue;
        }
        if(strcmp(command, "decompose") ==  0){
            handle_decompose();
        }else if(strcmp(command, "longest subsequence") == 0){
            handle_subsequence();
        }else if(strcmp(command, "exit") == 0){
            break;
        }else{
            display_help();
        }
    }

    return 0;
}