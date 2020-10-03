package grafos;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

/**
 * Essa classe implmenta uma estrutura de grafos utilizando HashMap. Os vertices
 * sao identificados por strings e suas arestas possuem peso.
 * @author Gabriel Van Loon
 *
 */
public class Grafo {
	
	private Map<String, Map<String, Integer>> grafo = new HashMap<String, Map<String, Integer>>();
	
	/**
	 * Recebe o path do arquivo que ira gerar o grafo. Caso o arquivo nao
	 * exista emite um exception.
	 * @param path
	 * @throws FileNotFoundException
	 */
	public Grafo(String path) throws FileNotFoundException {
		String arquivo = lerArquivo(path);
		String vertice = "";
		
		for (String linha : arquivo.split("\n")) {
			if(linha.startsWith("\t")) {
				String[] aresta = linha.split(" ");
				grafo.get(vertice).put(aresta[0].replace("\t", ""), Integer.parseInt(aresta[1]));
			} else {
				vertice = linha;
				grafo.put(vertice, new HashMap<String, Integer>());
			}
		}
	}
	
	/**
	 * Recebe o path do arquivo e retorna seu conteudo numa String.
	 * @param path
	 * @return Conteudo do arquivo
	 * @throws FileNotFoundException
	 */
	private String lerArquivo(String path) throws FileNotFoundException {
		Scanner in = null;
		String arquivo = "";
		
		try {
			in = new Scanner(new FileReader(path));
			
			while (in.hasNextLine()) {
				arquivo += in.nextLine() + "\n";
			}
			
			in.close();
		} catch (FileNotFoundException e) {
			throw new FileNotFoundException("Arquivo n�o encontrado.");
		}
		
		return arquivo;
	}
	
	/**
	 * Realiza o algoritmo de caminho minimo de Dijkstra. Recebe o vertice inicial e exibe na tela a
	 * distancia de todos os outros vertices a partir do vertice inicial.
	 * @param inicio
	 */
	void dijkstra(String inicio) {
		
		if (!grafo.containsKey(inicio)) {
			System.out.println("Vertice n�o existente.");
			return;
		}
		
		Map<String, Integer> distancia = new HashMap<String, Integer>();
		Map<String, Boolean> visitados = new HashMap<String, Boolean>();

		for (String vertice : grafo.keySet()) {
			distancia.put(vertice, Integer.MAX_VALUE);
			visitados.put(vertice, false);
		}

		distancia.put(inicio, 0);

		for (int count = 0; count < grafo.size(); count++) {

			String verticeAtual = menorAresta(distancia, visitados);
			
			visitados.put(verticeAtual, true);

			for (String vizinho: grafo.get(verticeAtual).keySet()) {
				if(!visitados.get(vizinho)
						&& distancia.get(verticeAtual) + grafo.get(verticeAtual).get(vizinho) < distancia.get(vizinho)) {
					distancia.put(vizinho, distancia.get(verticeAtual) + grafo.get(verticeAtual).get(vizinho));
				}
			}
		}

		for (String vertice : distancia.keySet()) {
			System.out.println(vertice + ": " + distancia.get(vertice));
		}
	}
	
	/**
	 * Funcao auxiliar do dijkstra. Retorna o label do Vertice que possui a 
	 * aresta de menor tamanho cujo vertice ainda nao foi visitado.
	 * @param distancia
	 * @param visitados
	 * @return
	 */
	String menorAresta(Map<String, Integer> distancia, Map<String, Boolean> visitados) 
    { 
        int distanciaMinima = Integer.MAX_VALUE;
        String indice = ""; 
  
        for (String vertice : distancia.keySet()) {
			if(!visitados.get(vertice) && distancia.get(vertice) <= distanciaMinima) {
				distanciaMinima = distancia.get(vertice);
				indice = vertice;
			}
		}
  
        return indice; 
    } 

}
