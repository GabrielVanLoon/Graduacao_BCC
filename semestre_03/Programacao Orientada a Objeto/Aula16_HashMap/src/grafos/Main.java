package grafos;

import java.io.FileNotFoundException;
import java.io.IOException;

/**
 * Exercicio de Java que implementa um algoritmo de caminho minimo em uma classe de Grafo.
 * O usuario insere o arquivo que ira gerar o grafo e em seguida o vertice que ira iniciar
 * o algoritmo.
 * @author Gabriel Van Loon
 *
 */
public class Main {

	public static void main(String[] args) {
		
	    try {
	    	System.out.println("Informe o path de arquivo texto:");
			String path = EntradaTeclado.leString();
			
			System.out.println("Informe o vertice de origem:");
			String origem = EntradaTeclado.leString();
			
			Grafo grafo = new Grafo(path);
			grafo.dijkstra(origem);
			
		} catch(FileNotFoundException ex) {
			System.out.println(ex.getMessage());
		} catch (IOException e) {
			System.out.println("Entrada Incorreta.");
		}
	}

}
