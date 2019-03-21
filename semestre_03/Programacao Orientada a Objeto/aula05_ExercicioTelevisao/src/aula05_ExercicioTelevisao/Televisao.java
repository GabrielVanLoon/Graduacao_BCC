package aula05_ExercicioTelevisao;
/**
 * Implementa as configurações de uma televisão. Porém a classe em si não
 * possui as ferramentas para alterar seus dados, sendo necessário utilizar
 * um objeto da classe ControleRemoto para ser devidamente manipulada.
 * 
 * @author Gabriel Van Loon
 *
 */

public class Televisao {
	private int canal  = 1;
	private int volume = 20;
	
	public Televisao() {
	}
	
	public int getCanal() {
		return canal;
	}
	public void setCanal(int canal) {
		this.canal = canal;
	}
	public int getVolume() {
		return volume;
	}
	public void setVolume(int volume) {
		this.volume = volume;
	}
}
