package exe01_Agenda;

import java.util.ArrayList;

public class Agenda {
	ArrayList<Pessoa> contatos;
	
	public Agenda(){
		this.contatos = new ArrayList<Pessoa>();
	}
	
	/**
	 * Adiciona um novo contato 'p' no final da Agenda.
	 * @param	p 
	 */
	public void adicionar(Pessoa p){
		if(p == null) throw new IllegalArgumentException ("Argumento inválido!");
		contatos.add(p);
	}
	
	/**
	 * Busca o index de um contato por meio de seus dados de identificação
	 * como Nome, CPF (Pessoas Fisicas) ou CNPJ (Pessoas Jurídicas).
	 * @param 	str
	 * @return 	index ou -1 em caso de erro
	 */
	public int indexOf(String str){
		for(int i = 0; i < contatos.size(); i++ ){
			Pessoa p = contatos.get(i);
			
			if(p instanceof PessoaFisica){
				PessoaFisica pf = (PessoaFisica) p;
				if(str.equals(pf.getCpf())) {
					return i;
				}
				
			} else if(p instanceof PessoaJuridica){
				PessoaJuridica pj = (PessoaJuridica) p;
				if(str.equals(pj.getCnpj())) {
					return i;
				}
				
			} else {
				if(str.equals(p.getNome())){
					return i;
				}
			}
		}
		return -1;
	}
	
	/**
	 * Busca uma pessoa na lista de contatos por meio do Nome, CPF
	 * ou CNPJ. Retorna null caso não exista.
	 * @param str
	 * @return
	 */
	public Pessoa pesquisar(String str){
		int i = indexOf(str);
		
		if(i >= 0) 
			return this.contatos.get(i);
		
		return null;
	}
	
	/**
	 * Identifica e remove uma pessoa na lista de contatos por meio de
	 * seu Nome, CPF ou CNPJ. Retorna false caso a pessoa não exista.
	 * @param str
	 * @return
	 */
	public boolean remover(String str){
		int i = indexOf(str);
		if(i >= 0) {
			contatos.remove(i);
			return true;
		}
		return false;
	}
	
	/**
	 * Ordena a lista de contatos utilizando o método de
	 * InsertionSort O(n²).
	 */
	public void ordenar() {
		int i, j;
		for(i = 1; i < contatos.size(); i++) {
			Pessoa r = contatos.get(i);
			
			j = i-1;
			Pessoa l = contatos.get(j);
			
			while(j >= 0 && compara(l, r)) {
			    contatos.set(j+1, l);
				j--;
			    if(j >= 0)l = contatos.get(j);
			}

			contatos.set(j+1, r);
		}
	}
	
	@Override
	public String toString() {
		String str = "";
		for(Pessoa p : contatos) {
			if(p instanceof PessoaFisica) {
				PessoaFisica pf = (PessoaFisica) p;
				str += pf + "\n";
				
			} else if(p instanceof PessoaJuridica) {
				PessoaJuridica pj = (PessoaJuridica) p;
				str += pj + "\n";
			
			} else {
				str += p + "\n";
			}
		}
		return str;
	}
	
	/**
	 * Compara dois objetos do tipo pessoa e retorna true caso seja necessário
	 * realizar um swap entre eles para ordená-los.
	 * @param l (left)
	 * @param r (right)
	 * @return true se estão desordenados.
	 */
	private boolean compara(Pessoa l, Pessoa r) {
		if(r instanceof PessoaFisica && l instanceof PessoaJuridica) {
			return true;
			
		} else if(r instanceof PessoaFisica && l instanceof PessoaFisica) {
			PessoaFisica rf = (PessoaFisica) r;
			PessoaFisica lf = (PessoaFisica) l;
			return ( rf.getCpf().compareTo(lf.getCpf()) < 0 ) ? true : false;
		
		} else if(r instanceof PessoaJuridica && l instanceof PessoaJuridica) {
			PessoaJuridica rj = (PessoaJuridica) r;
			PessoaJuridica lj = (PessoaJuridica) l;
			return ( rj.getCnpj().compareTo(lj.getCnpj()) < 0 ) ? true : false;
		}
		
		return false;
	}
	
	public static void main(String[] args) {
		Agenda a = new Agenda();
		
		// String nome, String dtNascimento, String endereco, String tel, String mail, String cpf, String estadoCivil
		PessoaFisica[] pf = new PessoaFisica[4];
		pf[0] = new PessoaFisica("Gabriel", "10/10/1997", "Rua 9 de Agosto", "(13) 1234-1234", 
									"mail@usp.br", "982.560.160-43", "Casado");
		pf[1] = new PessoaFisica("Pedro", "22/03/1995", "Rua 7 de Setembro", "(13) 1234-1234", 
				"mail2@usp.br", "275.105.510-99", "Solteiro");
		pf[2] = new PessoaFisica("Karlos", "03/12/1999", "Rua XV de julho", "(13) 1234-1234", 
				"mail3@usp.br", "181.353.280-01", "Viúvo");
		pf[3] = new PessoaFisica("Moana", "01/01/2000", "Av. Dom Pedro I", "(13) 1234-1234", 
				"mail4@usp.br", "862.941.680-74", "Solteiro");
		
		// ... String cnpj, String razaoSocial, String inscricao
		PessoaJuridica[] pj = new PessoaJuridica[4];
		pj[0] = new PessoaJuridica("Julia", "02/07/1992", "Av. Evangelista II", "(13) 1234-1234", 
									"inter@prise.com", "22.237.597/0001-25", "Juliaria & Jóias", "709.979.497.918");
		pj[1] = new PessoaJuridica("Robert", "02/07/1992", "R. São Leopoldino", "(13) 1234-1234", 
				"inter@prise2.com", "54.350.886/0001-22", "Robert Richards Dublagens", "715.428.513.136");
		pj[2] = new PessoaJuridica("Isadora", "02/07/1992", "R. Conselheiro Nébias", "(13) 1234-1234", 
				"inter@prise3.com", "73.729.876/0001-47", "Isadora Doces", "056.304.733.100");
		pj[3] = new PessoaJuridica("Johny", "02/07/1992", "Av. Trab. Sant Charlense", "(13) 1234-1234", 
				"inter@prise4.com", "37.258.269/0001-82", "Documentos e Exportações", "051.796.967.852");
		
		for(int i = 0; i < 4; i++) {
			a.adicionar(pf[i]);
			a.adicionar(pj[i]);
		}
		
		System.out.println("NÃO ORDENADO....");
		System.out.println(a);
		
		a.ordenar();
		
		System.out.println("ORDENADO....");
		System.out.println(a);
		
		System.exit(0);
	}
	
}
