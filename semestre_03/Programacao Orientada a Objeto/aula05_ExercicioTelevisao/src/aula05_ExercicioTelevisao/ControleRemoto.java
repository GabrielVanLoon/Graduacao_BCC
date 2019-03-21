package aula05_ExercicioTelevisao;

/**
 * Classe que serve para alterar as configurações de um objeto da classe
 * Televisao.
 * 
 * @author Gabriel Van Loon
 *
 */
public class ControleRemoto {
	private Televisao t;
	
	ControleRemoto(){
		this.t = new Televisao();
	}
	
	/**
	 * Aumenta o volume da televisao em 1 unid. Caso já esteja no volume
	 * máximo emite um aviso.
	 */
	public void aumentarVolume() {
		int volumeAtual = t.getVolume();
		
		if(volumeAtual >= 100) {
			System.out.println("Volume já está no máximo!");
		} else {
			t.setVolume(volumeAtual+1);
		}
	}
	
	/**
	 * Diminui o volume da televisao em 1 unid. Caso já esteja no volume
	 * mínimo (mudo) emite um aviso.
	 */
	public void diminuirVolume() {
		int volumeAtual = t.getVolume();
		
		if(volumeAtual == 0) {
			System.out.println("Volume já está no mudo!");
		} else {
			t.setVolume(volumeAtual-1);
		}
	}
	
	/**
	 * Exibe o volume atual da televisão
	 */
	public void exibirVolume() {
		System.out.println("Volume atual: " + t.getVolume());
	}
	
	/**
	 * Aumenta o canal em 1 unid.
	 */
	public void aumentarCanal() {
		int canalAtual = t.getCanal();
		t.setCanal(canalAtual+1);
	}
	
	/**
	 * Diminui o canal em 1 unid. caso já esteja no canal 1 não faz nada
	 */
	public void diminuirCanal() {
		int canalAtual = t.getCanal();
		if(canalAtual > 1) {
			t.setCanal(canalAtual-1);
		}
	}
	
	/**
	 * Muda o canal da televisao para o canal c. Caso não seja um canal
	 * válido emite uma mensagem de aviso.
	 * @param c
	 */
	public void mudarCanal(int c) {
		if(c <= 0) {
			System.out.println("Insira um canal válido!");
		} else {
			t.setCanal(c);
		}
	}
	
	/**
	 * Exibe o canal atual da Televisao.
	 */
	public void exibirCanal() {
		System.out.println("Canal atual: " + t.getCanal());
	}
	
	/**
	 * Implementação de testes da classe ControleRemoto.
	 * @param args
	 */
	public static void main(String[] args) {
		ControleRemoto cont = new ControleRemoto();
		
		cont.exibirVolume();
		cont.aumentarVolume();
		cont.aumentarVolume();
		cont.aumentarVolume();
		cont.diminuirVolume();
		cont.exibirVolume();
		
		cont.exibirCanal();
		cont.mudarCanal(-1);
		cont.mudarCanal(50);
		cont.aumentarCanal();
		cont.aumentarCanal();
		cont.exibirCanal();
	}
}
