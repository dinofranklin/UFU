/*
** Classe Coordenacao - Implementa um objeto Coordenacao
** acessado apenas pela classe principal Main e que esta
** associado a varios objetos Professor, GradeHoraria e
** Aluno. O objeto possui a variavel curso, um Array 
** professores de Professor, um outro Array estudantes
** de Aluno e mais um Array gradeshorarias de GradeHoraria,
** alem disso, possui um construtor e os metodos
** CadastrarGrade, CadastrarProfessor, CadastrarAluno,
** MostrarAluno, MostrarGrades, MostrarProfessores,
** BuscarAluno, BuscarGrade, BuscarProfessor, MatricularAluno,
** AtualizarAluno, MatricularProfessor e DesmatricularProfessor.
*/

import java.util.ArrayList;
import java.util.Arrays;
import javax.swing.*;

public class Coordenacao{
    String curso;
    ArrayList<Professor> professores;
    ArrayList<GradeHoraria> gradeshorarias;
    ArrayList<Aluno> estudantes;

    public Coordenacao(String curso){
        this.curso = curso;
        professores = new ArrayList<Professor> ();
        gradeshorarias = new ArrayList<GradeHoraria> ();
        estudantes = new ArrayList<Aluno> ();
    }

    void CadastrarGrade(){
        int ver, n;
        GradeHoraria g;
        ver = Integer.parseInt(JOptionPane.showInputDialog("Digite a versao da grade: "));
        g = new GradeHoraria(ver);
        n = Integer.parseInt(JOptionPane.showInputDialog("Numero de disciplinas: "));
        for(int i=0; i<n; ++i){
            g.CadastrarDisciplina();
        }
        gradeshorarias.add(g);
    }

    void CadastrarProfessor(){
        String nome;
        nome = JOptionPane.showInputDialog("Digite o nome do professor: ");
        Professor p = new Professor(nome);
        professores.add(p);
    }

    void CadastrarAluno(){
        String nome;
        int matricula;
        nome = JOptionPane.showInputDialog("Digite o nome do aluno: ");
        matricula = Integer.parseInt(JOptionPane.showInputDialog("Matricula do aluno: "));
        Aluno a = new Aluno(nome, matricula);
        estudantes.add(a);
    }

    void MostrarAlunos(){
        System.out.println("Numero de alunos cadastrados: " + estudantes.size());
        for(Aluno a: estudantes){
            a.MostrarDados();
            System.out.println("");
        }
    }

    void MostrarGrades(){
        System.out.println("Numero de disciplinas cadastradas: " + estudantes.size());
        for(GradeHoraria g: gradeshorarias){
            g.ImprimirGrade();
        }
    }

    void MostrarProfessores(){
        System.out.println("Numero de professores cadastrados: " + professores.size());
        for(Professor p: professores){
            p.ImprimirProfessor();
        }
    }

    Aluno BuscarAluno(String nome){
        for(Aluno a: estudantes){
            if(nome.equals(a.nome)){
                return a;
            }
        }
        return null;
    }

    GradeHoraria BuscarGrade(int grad){
        for(GradeHoraria g: gradeshorarias){
            if(grad == g.versao){
                return g;
            }
        }
        return null;
    }

    Professor BuscarProfessor(String nome){
        for(Professor p: professores){
            if(nome.equals(p.nome)){
                return p;
            }
        }
        return null;
    }

    void MatricularAluno(){
        String nome, disc;
        int grad;
        nome = JOptionPane.showInputDialog("Digite o nome do aluno: ");
        grad = Integer.parseInt(JOptionPane.showInputDialog("Digite a versao da grade: "));
        disc = JOptionPane.showInputDialog("Digite o nome da disciplina: ");
        Aluno a = BuscarAluno(nome);
        if(a == null){
            System.out.println("Erro! Aluno nao encontrado.");
            return;
        }
        GradeHoraria g = BuscarGrade(grad);
        if(g == null){
            System.out.println("Erro! Grade nao encontrada.");
            return;
        }
        DisciplinaCoord d = g.BuscarDisciplina(disc);
        a.Matricular(d);
    }

    void AtualizarAluno(){
        String nome, disc;
        int grad;
        double nota;
        nome = JOptionPane.showInputDialog("Digite o nome do aluno: ");
        grad = Integer.parseInt(JOptionPane.showInputDialog("Digite a versao da grade: "));
        disc = JOptionPane.showInputDialog("Digite o nome da disciplina: ");
        nota = Double.parseDouble(JOptionPane.showInputDialog("Digite a nota: "));
        Aluno a = BuscarAluno(nome);
        if(a == null){
            System.out.println("Erro! Aluno nao encontrado.");
            return;
        }
        GradeHoraria g = BuscarGrade(grad);
        if(g == null){
            System.out.println("Erro! Grade nao encontrada.");
            return;
        }
        DisciplinaCoord d = g.BuscarDisciplina(disc);
        a.AtualizarDisciplina(d,nota);
    }

    void MatricularProfessor(){
        String nome, disc;
        int grad;
        nome = JOptionPane.showInputDialog("Digite o nome do professor: ");
        grad = Integer.parseInt(JOptionPane.showInputDialog("Digite a versao da grade: "));
        disc = JOptionPane.showInputDialog("Digite o nome da disciplina: ");
        Professor p = BuscarProfessor(nome);
        if(p == null){
            System.out.println("Erro! Professor nao encontrado.");
            return;
        }
        GradeHoraria g = BuscarGrade(grad);
        if(g == null){
            System.out.println("Erro! Grade nao encontrada.");
            return;
        }
        DisciplinaCoord d = g.BuscarDisciplina(disc);
        p.CadastrarDisciplina(d);
    }

    void DesmatricularProfessor(){
        String nome, disc;
        int grad;
        nome = JOptionPane.showInputDialog("Digite o nome do professor: ");
        grad = Integer.parseInt(JOptionPane.showInputDialog("Digite a versao da grade: "));
        disc = JOptionPane.showInputDialog("Digite o nome da disciplina para remover: ");
        Professor p = BuscarProfessor(nome);
        if(p == null){
            System.out.println("Erro! Professor nao encontrado.");
            return;
        }
        GradeHoraria g = BuscarGrade(grad);
        if(g == null){
            System.out.println("Erro! Grade nao encontrada.");
            return;
        }
        DisciplinaCoord d = g.BuscarDisciplina(disc);
        p.RemoverDisciplina(d.nome);
    }
}