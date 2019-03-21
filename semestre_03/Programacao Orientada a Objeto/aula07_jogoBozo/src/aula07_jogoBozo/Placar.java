package aula07_jogoBozo;

public class Placar {
	
	private int   score;
	private int[] posicoes;
	
	public Placar() {
		score = 0;
		posicoes = new int[11];
		for(int i = 0; i < 11; i++) {
			posicoes[i] = -1;
		}
	}
	
	public int getScore() {
		return this.score;
	}
	
	public boolean posOcupada(int pos) {
		if(pos < 1 || pos > 10) return true;
		if(posicoes[pos] >= 0)  return true;
		return false;
	}
	
	public void add(int pos, int[] dados) {
		if( 1 <= pos && pos <= 6) {
			// Campos externos do tabuleiro
			int cont = 0;
			for(int i = 0; i < 5; i++) {
				if(pos == dados[i]) {
					cont++;
				}
			}
			this.posicoes[pos]  = cont * pos;;
			this.score         += cont * pos;
			
		} else if(pos == 7) {
			this.addFull(pos, dados);
		} else if(pos == 8) {
			this.addSeq(pos, dados);
		} else if(pos == 9) {
			this.addQuadra(pos, dados);
		} else if(pos == 10) {
			this.addQuina(pos, dados);
		} 
	}
	
	private void addFull(int pos, int[] dados) {
		int[]   cont = new int[7];
		boolean freq3 = false, freq2 = false;
		
		// Vetor que conta a frequencia de lados
		for(int i = 0; i < 7; i++) cont[i] = 0;
		for(int i = 0; i < 5; i++) cont[dados[i]]++;
		
		// Verifica se os 5 dados sao iguais ou 
		// se ha um valor com freq de 3 e outro com freq 2
		for(int i = 1; i < 7; i++) {
			if(cont[i] == 5) {
				freq3 = freq2 = true;
			} else if(cont[i] == 3) {
				freq3 = true;
			} else if(cont[i] == 2) {
				freq2 = true;
			}
		}
		
		if(freq3 && freq2) {
			this.score          += 15;
			this.posicoes[pos]   = 15;
		} else {
			this.posicoes[pos]   = 0;
		}
	}
	
	private void addSeq(int pos, int[] dados) {
		int[]   cont = new int[7];
		boolean seq15 = true, seq26 = true;
		
		// Vetor que conta a frequencia de lados
		for(int i = 0; i < 7; i++) cont[i] = 0;
		for(int i = 0; i < 5; i++) cont[dados[i]]++;
		
		// Testa sequencia 1,2,3,4,5
		for(int i = 1; i <= 5; i++) {
			if(cont[i] != 1) seq15 = false;
		}
		
		// Testa sequencia 1,2,3,4,5
		for(int i = 2; i <= 6; i++) {
			if(cont[i] != 1) seq26 = false;
		}
		
		if(seq15 || seq26) {
			this.score        += 20;
			this.posicoes[pos] = 20;
		} else {
			this.posicoes[pos] = 0;
		}
	}
	
	private void addQuadra(int pos, int[] dados) {
		int[]   cont = new int[7];
		boolean possuiQuadra = false;
		
		// Vetor que conta a frequencia de lados
		for(int i = 0; i < 7; i++) cont[i] = 0;
		for(int i = 0; i < 5; i++) cont[dados[i]]++;
		
		// Verifica se existe quadra
		for(int i = 1; i < 7; i++) {
			if(cont[i] >= 4) {
				possuiQuadra = true;
			} 
		}
		
		if(possuiQuadra) {
			this.score        += 30;
			this.posicoes[pos] = 30;
		} else {
			this.posicoes[pos] = 0;
		}
	}
	
	private void addQuina(int pos, int[] dados) {
		int[]   cont = new int[7];
		boolean possuiQuina = false;
		
		// Vetor que conta a frequencia de lados
		for(int i = 0; i < 7; i++) cont[i] = 0;
		for(int i = 0; i < 5; i++) cont[dados[i]]++;
		
		// Verifica se existe quina
		for(int i = 1; i < 7; i++) {
			if(cont[i] == 5) {
				possuiQuina = true;
			} 
		}
		
		if(possuiQuina) {
			this.score        += 40;
			this.posicoes[pos] = 40;
		} else {
			this.posicoes[pos] = 0;
		}
	}
	
	@Override
	public String toString() {
		
		String str = "";
		String[] strPos = new String[11];
		
		
		for(int i = 1; i < 10; i++) {
			strPos[i] = new String();
			strPos[i] = (posOcupada(i)) ? "    "+ String.format("%02d", this.posicoes[i])  +"pt   " : "    ["+ i +"]    ";
		}
		strPos[10] = new String();
		strPos[10] = (posOcupada(10)) ? "    "+ String.format("%02d", this.posicoes[10])  +"pt   " : "    [10]   ";
		
		str += "\t|" + strPos[1] + "|" + strPos[7] + "|" + strPos[4] + "| \t\t [7]:Full\n";
		str += "\t+-----------+-----------+-----------+\n";
		str += "\t|" + strPos[2] + "|" + strPos[8] + "|" + strPos[5] + "| \t\t [8]:Seq\n";
		str += "\t+-----------+-----------+-----------+\n";
		str += "\t|" + strPos[3] + "|" + strPos[9] + "|" + strPos[6] + "| \t\t [9]:Quadra\n";
		str += "\t+-----------+-----------+-----------+\n";
		str += "\t            |" + strPos[10] + "|             \t\t [10]:Quina\n";
		str += "\t            +-----------+          \n\n";
		
		
		str += "\tSCORE ATUAL: " + this.score + "\n" ;
		

		return str;
	}
}
