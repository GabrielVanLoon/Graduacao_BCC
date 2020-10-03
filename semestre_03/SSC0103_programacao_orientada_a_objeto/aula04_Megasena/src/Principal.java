import java.io.IOException;

public class Principal {
	
	public static void main(String[] args) throws IOException {
		// aula04();
		aula06();
	}
	
	// Aula 04 - Aprendendo sobre sobrecarga de construtores
	public static void aula04() throws IOException {
		System.out.print("Digite um numero inteiro para a semente: ");
		int s = EntradaTeclado.leInt();
		
		Random rTime = new Random();
		Random rFixo = new Random(s);
		
		int it = 0, num = 0;
		do {
			num = rTime.getIntRand(500)+1;
			it++;
		} while(num != rFixo.getIntRand(500)+1);
		
		System.out.println("Foram necessarias " + it + " iteraces para ambos Random() gerarem o numero " + num);
	}
	
	// Aula 06 - Aprendendo sobre sobrecarga de construtores
	public static void aula06() {
		
		Random r = new Random();
		
		// Transformando objeto em uma string
		System.out.println("Objeto Random(): " + r);
		
		// Testando a sobrecarga
		System.out.println("getRand(): " + r.getRand() );
		System.out.println("Funcao sem parametros: " + r.getIntRand());
		System.out.println("Funcao com valor max: "  + r.getIntRand(2));
		System.out.println("Funcao com min e max: "  + r.getIntRand(600, 800));
		
	}

}
