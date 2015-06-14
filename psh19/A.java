import java.util.Scanner;
import java.util.Arrays;

public class A {
    public static void main(String[] args) throws java.io.IOException{
	Scanner in = new Scanner(System.in);
	int N = in.nextInt();

        int ar[] = new int[N];
        int right[] = new int[N];
        int left[] = new int[N];

	for(int i=0;i<N;i++){
	    ar[i] = in.nextInt();
        }

        // count 1 (right)
        right[0] = (ar[0] == 1) ? 1 : 0;
        for(int i=1;i<N;i++){
	    right[i] = (ar[i] == 1) ? (right[i-1]+1) : (right[i-1]);
        }

        // count 0 (left)
        left[0] = (ar[N-1] == 0) ? 1 : 0;
        for(int i=N-2;i>=0;i--){
	    left[i] = (ar[i] == 0) ? (left[i+1]+1) : (left[i+1]);
        }


	/*
        for(int i=0;i<N;i++){
	    if(M == 0) break;
            if(i == N-1){
		if(M%2 == 0){
		    break;
		}
		else{
                    if(i!=0 && ar[i-1] < ar[i]){
                        ar[i-1] = -ar[i-1];
                    }
		    else {
                        ar[i] = -ar[i];
                    }
		    break;
		}

            }
	    if(ar[i] < 0){
		ar[i] = -ar[i];
	    }
	    else{
		if(M%2 == 0){
                    break;
		}
		else{
                    if(i!=0 && ar[i-1] < ar[i]){

                        ar[i-1] = -ar[i-1];
                    }
		    else {

                        ar[i] = -ar[i];
                    }
		    break;
		}
	    }
	    M--;
	}

	int sum = 0;
	for (int i : ar)
	    sum += i;
	System.out.println(sum);
        */
    }
}
