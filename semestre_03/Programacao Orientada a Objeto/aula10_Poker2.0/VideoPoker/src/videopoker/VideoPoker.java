package videopoker;

import classesauxiliares.EntradaTeclado;

public class VideoPoker {
	
	public static void main(String[] args) {
		Baralho b = new Baralho();
		Jogador j = new Jogador();
		
		
		System.out.println("\n\tBEM VINDO AO VIDEO POKER!!!\n");
		
		char jogar = 'y';
		while(jogar == 'y') {
			
			jogarRodada(b, j);
			
			if(j.getCreditos() > 0) {
				System.out.print("\n\tDeseja jogar outra rodada? (y/n): ");
				try {
					String opt = EntradaTeclado.leString().trim();
					jogar = opt.charAt(0);
				} catch(Exception e) {
					jogar = 'n';
				}
			} else {
				System.out.println("\n\tSEUS CREDITOS ACABARAM!");
				jogar = 'n';
			}
		}
		
		System.out.println("\n\tFIM DE JOGO!!!");
		System.out.println("\tSEU SALDO FINAL: "+ j.getCreditos() +" CREDITOS.");
		
		System.exit(0);
	}
	
	
	public static void jogarRodada(Baralho b, Jogador j) {
		System.out.println("\n\tINICIO DA RODADA!");
		System.out.println("\tpressione ENTER para começar...");
		try { EntradaTeclado.leString(); } catch(Exception e) { }
		
		/**
		 * Etapa de apostas. O jogador decide quantos creditos ira 
		 * apostar nessa rodada. 
		 */
		int aposta = 0;
		do {
			try {
				System.out.println("\tSALDO ATUAL DE CREDITOS: " + j.getCreditos());
				System.out.print("\tEntre com o valor da aposta: ");
				aposta = EntradaTeclado.leInt();
			} catch(Exception e) {	
				aposta = -1;
			} finally {
				if(aposta < 0 || aposta > j.getCreditos()) {
					System.out.println("\n\tPOR FAVOR, INSIRA UM VALOR VALIDO!\n");
					aposta = -1;
				}
			}
		} while(j.apostarCreditos(aposta) < 0);
		
		/**
		 * Etapa de trocas, o jogador compra as cartas e pode trocar as cartas de sua
		 * mao ate no maximo duas vezes.
		 */
		j.comprarMao(b);
		for(int i = 0; i < 2; i++) {
			String posicoes;
			try {
				System.out.println("\n\tSUA MAO:");
				j.mostrarMao();
				System.out.print("\n\tSelecione as cartas para trocar: ");
				
				posicoes = EntradaTeclado.leString();
				j.trocarCarta(b, posicoes);
			} catch(Exception e) {
				
			}
		}
		
		/**
		 * Mostrando a mao final para o jogador
		 */
		System.out.println("\n\tSUA MAO FINAL:");
		j.mostrarMao();
		System.out.println("\n\tpressione ENTER para ver o resultado...");
		try { EntradaTeclado.leString(); } catch(Exception e) { }
		
		/**
		 * Resultado da aposta. Mostra se e quantos creditos o jogador ganhou.
		 */
		Mesa m = new Mesa();
		int multiplicador = m.aposta(j.getCartas());
		
		if(multiplicador == 0) {
			System.out.println("\tVOCE NAO FEZ NENHUMA COMBINAÇAO E PERDEU A APOSTA!");
		} else {
			System.out.println("\tVOCE FEZ A COMBINAÇAO: " + m.strCombinacao(multiplicador));
			System.out.println("\tPREMIO: " + (aposta*multiplicador) + " CREDITOS");
			j.receberCreditos(aposta*multiplicador);
		}
		
		System.out.println("\n\tSEU SALDO DE CREDITOS ATUAL: " + j.getCreditos());
		
		
		/**
		 * Resetando o baralho para a proxima rodada
		 */
		b.reset();
	}
}
