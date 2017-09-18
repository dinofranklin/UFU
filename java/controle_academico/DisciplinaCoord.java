/* 
** Classe DisciplinaCoord - implementa um objeto
** disciplina acessado pela Coordenacao. O objeto
** possui as variaveis nome, unidade, hrs_praticas
** hrs_teoricas e hrs_totais, um construtor e o 
** metodo ImprimirDisciplina.
*/

public class DisciplinaCoord{
    String nome, unidade;
    int hrs_praticas, hrs_teoricas, hrs_totais;

    public DisciplinaCoord(String nome, String und, int hp, int ht){
        this.nome = nome;
        this.unidade = und;
        this.hrs_praticas = hp;
        this.hrs_teoricas = ht;
        this.hrs_totais = hp+ht;
    }

    void ImprimirDisciplina(){
        System.out.println("Nome da disciplina: " + this.nome);
        System.out.println("Unidade: " + this.unidade);
        System.out.println("Horas praticas: " + this.hrs_praticas);
        System.out.println("Horas teoricas: " + this.hrs_teoricas);
        System.out.println("Horas totais: " + this.hrs_totais);
    }
}