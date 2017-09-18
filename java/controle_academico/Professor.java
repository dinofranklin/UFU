/*
** Classe Professor - Implementa um objeto Professor
** acessado pela Coordenacao e que esta associado a
** 3 objetos DisciplinaCoord. O objeto possui as
** variaveis nome, horas_aula, e DisciplinaCoord d1,
** d2 e d3, um construtor e os metodos CadastrarDisciplina,
** RemoverDisciplina e ImprimirProfessor.
*/

public class Professor{
    String nome;
    int horas_aula;
    DisciplinaCoord d1, d2, d3;
    
    public Professor(String nome){
        this.nome = nome;
    }

    void CadastrarDisciplina(DisciplinaCoord d){
        if(d1 == null){
            this.d1 = d;
            this.horas_aula += d.hrs_totais;
        }
        else if(d2 == null){
            this.d2 = d;
            this.horas_aula += d.hrs_totais;
        }
        else if(d3 == null){
            this.d3 = d;
            this.horas_aula += d.hrs_totais;
        }
        else{
            System.out.println("Nao foi possivel cadastrar disciplina!");
            System.out.println("O professor nao pode lecionar mais de 3 disciplinas.");
        }
    }

    void RemoverDisciplina(String nome){
        if(nome.equals(d1.nome)){
            this.horas_aula -= d1.hrs_totais;
            this.d1 = null;
        }
        else if(nome.equals(d2.nome)){
            this.horas_aula -= d2.hrs_totais;
            this.d2 = null;
        }
        else if(nome.equals(d3.nome)){
            this.horas_aula -= d3.hrs_totais;
            this.d3 = null;
        }
        else{
            System.out.println("Nao foi possivel remover disciplina!");
            System.out.println("A disciplina nao foi encontrada no cadastro.");
        }
    }

    void ImprimirProfessor(){
        int c = 1;
        System.out.println("Nome do Professor: " + this.nome);
        System.out.println("Horas-aula: " + this.horas_aula);
        if(d1 != null) System.out.println("Disciplina " + (c++) + ": " + d1.nome);
        if(d2 != null) System.out.println("Disciplina " + (c++) + ": " + d2.nome);
        if(d3 != null) System.out.println("Disciplina " + (c++) + ": " + d3.nome);
        System.out.println("");
    }

}