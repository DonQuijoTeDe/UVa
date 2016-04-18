package Partition_Integer;

import java.math.BigInteger;
import java.util.Scanner;

public class Main {

    static BigInteger table[][] = new BigInteger[2][5001];
	
	static void constructtable() {
		for(int i=0;i<2;i++) {
			for(int j=0;j<=5000;j++)
				table[i][j] = BigInteger.ZERO;
		}
		table[0][0] = BigInteger.ONE;
		for(int i=1;i<=5000;i++) {
			for(int j=0;j<=5000;j++) {
				if(j-i>=0)
					table[1][j] = table[0][j].add(table[1][j-i]);
				else
					table[1][j] = table[0][j];
			}
			for(int j=0;j<=5000;j++)
				table[0][j] = table[1][j];
		}
	}
	
	public static void main(String[] args) {
		constructtable();
		Scanner input = new Scanner(System.in);
		while(input.hasNext()) {
			int n = input.nextInt();
			System.out.println(table[1][n]);
		}
		input.close();
	}

}
