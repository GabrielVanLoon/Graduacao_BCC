import java.io.IOException;

public class MegaSena {

	public static void main(String[] args) throws IOException {
		// Gera um objeto da classe Random()
		// Random rand = new Random();
		
		// System.out.print("Digite um numero inteiro para a semente: ");
		// int s = EntradaTeclado.leInt();
		// rand.setSemente(s);
		
		System.out.print("Digite um numero inteiro para a semente: ");
		int s = EntradaTeclado.leInt();
		Random rand = new Random(s);
		
		for(int i = 0; i < 6; i++){
			// Gerar numero de 1 à 60
			int num = rand.getIntRand(60) + 1;
			System.out.println(i+1 + "º Numero: " + num);
		}
	}

}
