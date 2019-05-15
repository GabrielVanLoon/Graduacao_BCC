
public class Contas {

	private ContaBancaria contas[] = new ContaBancaria[100];
	private int nContas = 0;
	
	public static void main(String[] args) throws Exception {
		int op = 0, conta, dia;
		Contas ct = new Contas();
		String s;
		
		while (op != 8) {
			op = ct.leOpcao();
			
			switch (op)
			{
			case 1: // Criar conta Poupança Simples
				System.out.print("Nome do correntista: ");
				s = EntradaTeclado.leString();
				System.out.print("Dia de vencimento: ");
				dia = EntradaTeclado.leInt();
				PoupancaSimples cps = new PoupancaSimples(s, dia);
				ct.add(cps);
				System.out.println("************ Conta criada.**************");
				break;
				
			case 2: // Criar conta Poupanca gold
				System.out.print("Nome do correntista: ");
				s = EntradaTeclado.leString();
				System.out.print("Dia de vencimento: ");
				dia = EntradaTeclado.leInt();
				PoupancaOuro cpo = new PoupancaOuro(s, dia);
				ct.add(cpo);
				System.out.println("************ Conta criada.**************");
				break;
				
			case 3: // Criar Conta Especial
				System.out.print("Nome do correntista: ");
				s = EntradaTeclado.leString();
				System.out.print("Limite de saque: ");
				double limite = EntradaTeclado.leDouble();
				ContaEspecial ce = new ContaEspecial(s, limite);
				ct.add(ce);
				System.out.println("************ Conta criada.**************");
				break;
				
			case 4: // Realizar saque
				System.out.print("Numero da conta: ");
				conta = EntradaTeclado.leInt();
				System.out.print("Valor a sacar: ");
				double valor = EntradaTeclado.leDouble();
				ContaBancaria cb = ct.procura(conta);
				if ( cb == null )
				{
					System.out.println("************* Conta não existe **************");
					break;
				}
				try {
					cb.saca(valor);
					System.out.println("****************** Saque realizado ***********");
				}
				catch (Exception e)
				{
					System.out.println("****************** Saque não realizado ***********");
					System.out.println(e.getMessage());
				}
				break;
				
			case 5: // Realizar depósito
				System.out.print("Numero da conta: ");
				conta = EntradaTeclado.leInt();
				System.out.print("Valor a depositar: ");
				valor = EntradaTeclado.leDouble();
				cb = ct.procura(conta);
				if ( cb == null )
				{
					System.out.println("************* Conta não existe **************");
					break;
				}
				cb.deposita(valor);
				System.out.println("****************** Depósito realizado ***********");
				break;
			
			case 6: // Atualizar poupanças
				System.out.print("Qual o valor da taxa? ");
				double tx = EntradaTeclado.leDouble();
				ct.atualizaPoupança(tx);
				System.out.println("Saldos atualizados");
				break;
				
			case 7: // Mostrar saldos
				ct.printSaldos();
				break;
				
				
			case 8: // Sair do programa
				System.out.println("Terminando o programa....");
				return;
			}
			
			System.out.println("Digite ENTER para continuar");
			try { EntradaTeclado.leString(); } catch(Exception e) {}
			System.out.println("\n\n");
		}

	}

	private int leOpcao() {
        System.out.println(   "1) Criar poupança simples\n"
        					+ "2) Criar poupança gold\n"
        					+ "3) Criar conta especial\n"
        					+ "4) Realizar saque\n"
        					+ "5) Realizar deposito\n"
        					+ "6) Atualizar poupanças\n"
        					+ "7) Mostrar saldos\n"
        					+ "8) Sair");
        int k = -1;
        while (true)
        {
        	System.out.print("Digite a opção desejada ===> ");
        	try {
        		k = EntradaTeclado.leInt();
        		if ( k > 0 && k <= 8 )
        			return k;
        	}
        	catch (Exception e) {
        		
        	}
        }
	}

	private void add(ContaBancaria cb) {
		contas[nContas++] = cb;		
	}
	
	private void printSaldos() {
		for (ContaBancaria ctb : contas)
		{
			if ( ctb == null ) break;
			System.out.println("Numero da conta:" + ctb.getNumConta());
			System.out.println("Titular: "        + ctb.getNomeCliente());
			System.out.println("Saldo: "          + ctb.getSaldo());
			System.out.println();
		}

	}

	private void atualizaPoupança(double tx) {
		for (ContaBancaria ctb : contas)
		{
			if ( ctb == null ) break;

			ctb.atualiza(tx);
			
			//if ( ctb instanceof PoupancaSimples ) {
			//	PoupancaSimples cp = (PoupancaSimples) ctb;
			//	cp.atualiza(tx);
				
			//} else if( ctb instanceof PoupancaOuro ) {
			//	PoupancaOuro cp = (PoupancaOuro) ctb;
			//	cp.atualiza(tx);
			//} 
			
		}
	}

	private ContaBancaria procura(int conta) {
		for (ContaBancaria ctb: contas )
		{
			if ( ctb == null ) break;

			if (conta == ctb.getNumConta())
				return ctb;
		}
		return null;
	}

}
