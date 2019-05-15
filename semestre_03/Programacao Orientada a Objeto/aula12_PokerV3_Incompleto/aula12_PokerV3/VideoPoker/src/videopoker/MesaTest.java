package videopoker;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

public class MesaTest {
	
	Mesa m;
	
	@Before
	public void setup(){
		m = new Mesa();
	}

	@Test
	public void testAposta() {
		// Caso 1: Cartas sem nenhum padrão, pois de tabela irá testar o caso negativo
		// dos outros 3 métodos abaixo.
		Carta[] c = new Carta[5];
		c[0] = new Carta(5,  1);
		c[1] = new Carta(7,  1);
		c[2] = new Carta(9,  2);
		c[3] = new Carta(4,  1);
		c[4] = new Carta(11, 1);
		
		int result = m.aposta(c);
		assertEquals(0, result);
	}
	
	
	@Test
	public void testCheckStraightFlush1() {
		// Testando apenas Straight
		Carta[] c = new Carta[5];
		c[0] = new Carta(5, 1);
		c[1] = new Carta(6, 2);
		c[2] = new Carta(7, 1);
		c[3] = new Carta(8, 0);
		c[4] = new Carta(9, 0);
		
		int[] n    = new int[c.length];
		for (int i = 0; i < n.length; i++) {
			n[i] = c[i].getNumero();
		}
		
		int result = m.checkStraightFlush(c, n);
		assertEquals(5, result);
	}
	
	@Test
	public void testCheckStraightFlush2() {
		// Testando apenas Flush
		Carta[] c = new Carta[5];
		c[0] = new Carta(2, 1);
		c[1] = new Carta(6, 1);
		c[2] = new Carta(7, 1);
		c[3] = new Carta(8, 1);
		c[4] = new Carta(9, 1);
		
		int[] n    = new int[c.length];
		for (int i = 0; i < n.length; i++) {
			n[i] = c[i].getNumero();
		}
		
		int result = m.checkStraightFlush(c, n);
		assertEquals(10, result);
	}
	
	@Test
	public void testCheckStraightFlush3() {
		// Testando apenas Straight Flush
		Carta[] c = new Carta[5];
		c[0] = new Carta(5, 1);
		c[1] = new Carta(6, 1);
		c[2] = new Carta(7, 1);
		c[3] = new Carta(8, 1);
		c[4] = new Carta(9, 1);
		
		int[] n    = new int[c.length];
		for (int i = 0; i < n.length; i++) {
			n[i] = c[i].getNumero();
		}
		
		int result = m.checkStraightFlush(c, n);
		assertEquals(100, result);
	}
	
	/**
	@Test
	public void testCheckSequenciaNum() {
		fail("Not yet implemented");
	}

	@Test
	public void testStrCombinacao() {
		fail("Not yet implemented");
	}
	*/
}
