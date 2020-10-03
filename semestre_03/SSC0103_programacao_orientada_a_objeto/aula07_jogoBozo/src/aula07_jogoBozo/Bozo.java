package aula07_jogoBozo;

import java.io.IOException;

public class Bozo {

	public static void main(String[] args) throws IOException {
		Placar      placar = new Placar();
		RolaDados	dados  = new RolaDados(5);
		int[]       aux;
		int         pos;
		
		for(int rodada = 1; rodada <= 10; rodada++) {
			/** Início da Rodada **/
			System.out.println("\tRODADA Nº"+ rodada);
			System.out.println("\tpressione ENTER para começar...");
			System.in.read();
			
			/** Rolagem dos dados **/ 
			aux = dados.rolar();
			System.out.println("\t1ª ROLAGEM:"); 
			dados.verDados(aux);
			
			for(int rol = 2; rol <= 3; rol++ ) {
				System.out.print("\tDigite os dados que deseja trocar: ");
				aux = dados.rolar(EntradaTeclado.leString());
				System.out.println("\n\t" + rol + "ª ROLAGEM: "); 
				dados.verDados(aux);
			}
			
			/** Placar atual **/
			System.out.println("\n\tPLACAR ATUAL:\n" + placar);
			do {
				System.out.print("\tSelecione a posição dos dados: ");
				try{
					pos = EntradaTeclado.leInt();
				} catch(Exception e) {
					pos = -1;
				}
			} while(placar.posOcupada(pos));
			
			/** Insere os dados e exibe o placar atualizado **/
			placar.add(pos, aux);
			System.out.println("\n\tPLACAR ATUAL:\n" + placar);
			System.out.println("\n\n\n\n");
		}
		
		System.out.println("\tSEU PLACAR FINAL: " + placar.getScore());
		
	}

}
