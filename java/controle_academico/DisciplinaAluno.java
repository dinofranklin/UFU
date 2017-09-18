/*
** Classe DisciplinaAluno - implementa um objeto 
** disciplina acessada pelo Historico. O objeto possui
** as variaveis nome, situacao e nota, um construtor
** e os metodos AtualizarDisciplina e ImprimirDisciplina 
*/

public class DisciplinaAluno{
    String nome;
    SituacaoDisciplina situacao;
    double nota;

    public DisciplinaAluno(String nome){
        this.nome = nome;
        this.situacao = SituacaoDisciplina.CURSANDO;
    }

    void AtualizarDisciplina(double nota){
        this.nota = nota;
        if(nota >= 60.0){
            this.situacao = SituacaoDisciplina.APROVADO;
        }
        else{
            this.situacao = SituacaoDisciplina.REPROVADO;
        }
    }

    void ImprimirDisciplina(){
        System.out.println(this.nome + " - " + this.nota + ": " + this.situacao);
    }

}