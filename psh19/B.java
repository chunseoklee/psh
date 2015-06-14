import java.util.Scanner;
import java.util.Arrays;

public class B {
    public static void main(String[] args) throws java.io.IOException{
	Scanner in = new Scanner(System.in);
	int N = in.nextInt();
	int M = in.nextInt();
	int ar[] = new int[N];

	for(int i=0;i<N;i++){
	    ar[i] = in.nextInt();
	    //System.out.println(ar[i]);

	}
	Arrays.sort(ar);
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

    }
}
