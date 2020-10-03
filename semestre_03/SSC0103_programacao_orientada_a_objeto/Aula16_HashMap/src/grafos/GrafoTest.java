package grafos;

import java.io.FileNotFoundException;

import org.junit.Test;

public class GrafoTest {

	@Test(expected=Test.None.class)
	public void testLeituraGrafo() throws FileNotFoundException {
		Grafo grafo = new Grafo("src/grafo.txt");
	}
	
	@Test(expected=FileNotFoundException.class)
	public void testLeituraGrafoArquivoNaoEncontrato() throws FileNotFoundException {
		Grafo grafo = new Grafo("src/grafo_123.txt");
	}
	
	@Test(expected=Test.None.class)
	public void testDijkstra() throws FileNotFoundException {
		Grafo grafo = new Grafo("src/grafo.txt");
		grafo.dijkstra("S�o_Carlos");
	}
	
	@Test(expected=Test.None.class)
	public void testDijkstraOrigemNaoEncontrada() throws FileNotFoundException {
		Grafo grafo = new Grafo("src/grafo.txt");
		grafo.dijkstra("S�o_Vicente");
	}

}
