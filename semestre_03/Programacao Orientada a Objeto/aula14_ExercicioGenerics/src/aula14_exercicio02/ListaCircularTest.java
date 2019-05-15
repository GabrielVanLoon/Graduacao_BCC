package aula14_exercicio02;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import aula14_exercicio01.Par;

/**
 * Classe de testes unitários da classe ListaCircular.
 * @author gabriel van loon
 *
 */
public class ListaCircularTest {
	
	private ListaCircular<Par<Integer, Double>> l;
	
	@Before
	public void estanciarLista() {
		l = new ListaCircular<Par<Integer, Double>>();
	}
	
	/**
	 * Inserir elementos no início até preencher toda a lista.
	 */
	@Test
	public void testeInserirInicio() {
		for(int i = 1; i <= ListaCircular.capacidade(); i++) {
			assertEquals(true, l.inserirInicio(new Par<Integer,Double>(i, i*1.75)));
		}
		assertEquals(false, l.inserirInicio(new Par<Integer,Double>(10, 19.45)));
	}
	
	/**
	 * Inserir elementos no início até preencher toda a lista.
	 */
	@Test
	public void testeInserirFim() {
		for(int i = 1; i <= ListaCircular.capacidade(); i++) {
			assertEquals(true, l.inserirFim(new Par<Integer,Double>(i, i*1.75)));
		}
		assertEquals(false, l.inserirFim(new Par<Integer,Double>(10, 19.45)));
	}
	
	/**
	 * Remove todos os elementos pelo início
	 */
	@Test
	public void testeRemoverPrimeiro() {
		@SuppressWarnings("unchecked")
		Par<Integer,Double>[] pares = new Par[ListaCircular.capacidade()];
		
		for(int i = 1; i <= ListaCircular.capacidade(); i++) {
			l.inserirInicio(new Par<Integer,Double>(i, i*1.75));
			pares[i-1] = new Par<Integer,Double>(i, i*1.75);
		}
		
		for(int i = 1; i <= ListaCircular.capacidade(); i++) {
			Par<Integer, Double> p = l.removerPrimeiroElemento();
			assertEquals(pares[10-i].getChave(), p.getChave());
			assertEquals(pares[10-i].getValor(), p.getValor());
		}
		
		assertEquals(null, l.removerPrimeiroElemento());
	}
	
	/**
	 * Remove todos os elementos pelo fim
	 */
	@Test
	public void testeRemoverUltimo() {
		@SuppressWarnings("unchecked")
		Par<Integer,Double>[] pares = new Par[ListaCircular.capacidade()];
		
		for(int i = 1; i <= ListaCircular.capacidade(); i++) {
			l.inserirInicio(new Par<Integer,Double>(i, i*1.75));
			pares[i-1] = new Par<Integer,Double>(i, i*1.75);
		}
		
		for(int i = 1; i <= ListaCircular.capacidade(); i++) {
			Par<Integer, Double> p = l.removerUltimoElemento();
			assertEquals(pares[i-1].getChave(), p.getChave());
			assertEquals(pares[i-1].getValor(), p.getValor());
		}
		
		assertEquals(null, l.removerUltimoElemento());
	}
	
	/**
	 * Testando branch ao inserir no fim
	 */
	@Test
	public void inserirFim2() {
		estanciarLista();
		
		for(int i = 1; i <= ListaCircular.capacidade(); i++) {
			l.inserirFim(new Par<Integer,Double>(i, i*1.75));
		}
		
		//Removo os dois primeiros para forçar o inicio a sair do 0
		for(int i = 1; i <= 6; i++) {
			l.removerPrimeiroElemento();
		}
		
		for(int i = 1; i <= 6; i++) {
			assertEquals(true, l.inserirFim(new Par<Integer,Double>(i+20, i*2.50)));
		}
	}
	
	
	
	
}
