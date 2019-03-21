package aula02_dadosPrimitivos;

import java.io.IOException;

public class EqSegundoGrau {

	public static void main(String[] args) throws IOException {
		
		double 	a = 0, b = 0, c = 0;
		boolean ok = false;
		
		while(!ok) {
			try {
				System.out.print("Digite o valor de a: ");
				a = EntradaTeclado.leDouble();
				ok = true;
			} catch(Exception e) {
				System.out.println("O valor informado não é numérico. Insira novamente!");
			}
		} ok = false;
		
		while(!ok) {
			try {
				System.out.print("Digite o valor de b: ");
				b = EntradaTeclado.leDouble();
				ok = true;
			} catch(Exception e) {
				System.out.println("O valor informado não é numérico. Insira novamente!");
			}
		} ok = false;
		
		while(!ok) {
			try {
				System.out.print("Digite o valor de c: ");
				c = EntradaTeclado.leDouble();
				ok = true;
			} catch(Exception e) {
				System.out.println("O valor informado não é numérico. Insira novamente!");
			}
		} ok = false;
		
		System.out.printf("Equação: %.2fx^2 + %.2fx + %.2f.\n", a, b, c);
		
		double delta = (b*b)-(4*a*c);
		
		if(delta < 0) {
			System.out.printf("Essa equação não possui raízes.\n");
		} else {
			double x1 = (-b + Math.sqrt(delta))/(2*a);
			double x2 = (-b + Math.sqrt(delta))/(2*a);
			System.out.printf("As raízes são %.2f e %.2f.\n", x1, x2);
		}
		
		
		
	}

}
