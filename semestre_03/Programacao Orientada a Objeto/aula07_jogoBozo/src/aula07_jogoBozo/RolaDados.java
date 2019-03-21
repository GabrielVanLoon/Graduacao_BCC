package aula07_jogoBozo;

public class RolaDados {
	
	private Dado[] dados;
	private int    qtdDados;
	
	public RolaDados(int n) {
		this.qtdDados = n;
		this.dados    = new Dado[n];
		
		Random r = new Random();
		for(int i = 0; i < qtdDados; i++) {
			this.dados[i] = new Dado(1, r);
		}
	}
	
	public int[] rolar() {
		int[] r = new int[qtdDados];
		for(int i = 0; i < qtdDados; i++) {
			r[i] = dados[i].rolar();
		}
		return r;
	}
	
	public int[] rolar(boolean[] quais) {
		int[] r = new int[qtdDados];
		for(int i = 0; i < qtdDados; i++) {
			if(quais[i]) {
				r[i] = dados[i].rolar();
			} else {
				r[i] = dados[i].getLado();
			}
		}
		return r;
	}
	
	public int[] rolar(String s) {
		boolean[] girar = new boolean[qtdDados];
		String[]  dados = s.split(" ");
		
		// Configura todos para falso
		for(int i = 0; i < girar.length; ++i){
		    girar[i] = false;
		}
		
		// Muda quais vao ser girados
		for(int i = 0; i < dados.length; i++) {
			try {
				int d = Integer.parseInt(dados[i]) - 1;
				if(0 <= d && d < qtdDados) { 
					girar[d] = true; 
				} 
			} catch(Exception e) {
				// Nada acontece feijoada
			}
		}
		return this.rolar(girar);
	}
	
	@Override
	public String toString() {
		String str = "";
		for(int i = 0; i < this.qtdDados; i++) {
			// str += (i+1) + "º:" +this.dados[i] + " ";
			str += (i+1) + "º Dado: " + this.dados[i] + " | ";
		}
		return str;
	}
	
	public void verDados(int[] dados) {
		/** Configurando as strings dos dados **/
		String   traco = "+---------+";
		String[] linha1 = new String[7];
		String[] linha2 = new String[7];
		String[] linha3 = new String[7];
		
		linha1[1] = "|         |";
		linha2[1] = "|    *    |";
		linha3[1] = "|         |";
		
		linha1[2] = "| *       |";
		linha2[2] = "|         |";
		linha3[2] = "|       * |";

		linha1[3] = "| *       |";
		linha2[3] = "|    *    |";
		linha3[3] = "|       * |";
		
		linha1[4] = "| *     * |";
		linha2[4] = "|         |";
		linha3[4] = "| *     * |";
		
		linha1[5] = "| *     * |";
		linha2[5] = "|    *    |";
		linha3[5] = "| *     * |";
		
		linha1[6] = "| *     * |";
		linha2[6] = "| *     * |";
		linha3[6] = "| *     * |";
		
		/** Gerando a string para visualizar **/
		String strLinha0 = "\t";
		String strLinha1 = "\t";
		String strLinha2 = "\t";
		String strLinha3 = "\t";
		String strLinha4 = "\t";
		String strLinha5 = "\t";
		
		for(int i = 0; i < qtdDados; i++) {
			strLinha0 += traco + "   ";
			strLinha1 += linha1[dados[i]] + "   ";
			strLinha2 += linha2[dados[i]] + "   ";
			strLinha3 += linha3[dados[i]] + "   ";
			strLinha4 += traco + "   ";
			strLinha5 += "     " + dados[i] + "     " + "   ";
		}

		System.out.println(strLinha0);
		System.out.println(strLinha1);
		System.out.println(strLinha2);
		System.out.println(strLinha3);
		System.out.println(strLinha4);
		System.out.println(strLinha5);
		System.out.println();
	}
	
}
