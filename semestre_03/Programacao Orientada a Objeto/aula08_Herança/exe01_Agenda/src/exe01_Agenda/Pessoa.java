package exe01_Agenda;

public class Pessoa {
	private String nome;
	private String dtNascimento;
	private String endereco;
	private String telefone;
	private String email;
	
	public Pessoa(){	
	}
	
	public Pessoa(String nome, String dtNascimento, String endereco, String tel, String mail){
		this.nome = nome;
		this.dtNascimento = dtNascimento;
		this.endereco = endereco;
		this.telefone = tel;
		this.email = mail;
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public String getDtNascimento() {
		return dtNascimento;
	}

	public void setDtNascimento(String dtNascimento) {
		this.dtNascimento = dtNascimento;
	}

	public String getEndereco() {
		return endereco;
	}

	public void setEndereco(String endereco) {
		this.endereco = endereco;
	}

	public String getTelefone() {
		return telefone;
	}

	public void setTelefone(String telefone) {
		this.telefone = telefone;
	}

	public String getEmail() {
		return email;
	}

	public void setEmail(String email) {
		this.email = email;
	}
	
	@Override
	public String toString() {
		String str = "";
		str += "Nome: " + getNome() + "\tNascimento: " + getDtNascimento() + "\n";
		str += "E-mail: " + getEmail() + "\tTelefone: " + getTelefone() + "\n"; 
		str += "Endereço: " + getEndereco() + "\n"; 
		return str;
	}
	
}
