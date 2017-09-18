/*
** Classe Aluno - implementa um objeto Aluno que e
** acessado pela Coordenacao e que esta associado
** a um objeto Historico. O objeto possui as variveis
** nome, matricula e um Historico hist, um construtor
** e os metodos Matricular, AtualizarDisciplina e
** MostrarDados. 
*/

public class Aluno{
    String nome;
    int matricula;
    Historico hist;

    public Aluno(String nome, int matricula){
        this.nome = nome;
        this.matricula = matricula;
        this.hist = new Historico();
    }

    void Matricular(DisciplinaCoord d){
        this.hist.MatricularDisciplina(d);
    }

    void AtualizarDisciplina(DisciplinaCoord d, double nota){
        this.hist.AtualizarHistorico(d.nome, nota);
    }

    void MostrarDados(){
        System.out.println("Aluno: " + nome);
        System.out.println("Matricula: " + matricula);
        hist.ImprimirHistorico();
    }
}