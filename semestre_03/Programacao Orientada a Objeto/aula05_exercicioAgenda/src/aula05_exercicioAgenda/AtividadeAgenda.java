package aula05_exercicioAgenda;

public class AtividadeAgenda {

	public static void main(String[] args) {
		Agenda a = new Agenda();
		
		a.armazenaPessoa("Gabriel", 21, 1.75f);
		a.armazenaPessoa("Chris", 28, 1.79f);
		a.armazenaPessoa("Josué", 17, 1.55f);
		a.armazenaPessoa("Tamiris", 19, 1.68f);
		
		a.imprimeAgenda();
		
		a.removePessoa("Josué");
		
		a.imprimeAgenda();
	}

}
