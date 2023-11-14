#include <iostream>
#include <unordered_map>
#include <functional>
#include <memory>

using namespace std;

// Interfaz de comando
class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() {}
};

// Comandos concretos
class DespegarCommand : public Command {
public:
    void execute() override {
        cout << "Despegando el dron.\n";
    }
};

class AterrizarCommand : public Command {
public:
    void execute() override {
        cout << "Aterrizando el dron.\n";
    }
};

class GiroDerechaCommand : public Command {
public:
    void execute() override {
        cout << "Girando a la derecha.\n";
    }
};

class GiroIzquierdaCommand : public Command {
public:
    void execute() override {
        cout << "Girando a la izquierda.\n";
    }
};

// Invocador
class Invoker {
private:
    unordered_map<char, unique_ptr<Command> > commands;

public:
    void setCommand(char key, unique_ptr<Command> command) {
        commands[key] = move(command);
    }

    void executeCommand(char key) {
        auto it = commands.find(key);
        if (it != commands.end()) {
            it->second->execute();
        } else {
            std::cout << "Opción no válida.\n";
        }
    }
};

int main() {
    Invoker invoker;

    // Configurar comandos
    invoker.setCommand('1', std::unique_ptr<DespegarCommand>(new DespegarCommand()));
    invoker.setCommand('1', std::unique_ptr<AterrizarCommand>(new AterrizarCommand()));
    invoker.setCommand('1', std::unique_ptr<GiroDerechaCommand>(new GiroDerechaCommand()));
    invoker.setCommand('1', std::unique_ptr<GiroIzquierdaCommand>(new GiroIzquierdaCommand()));

    char option;
    do {
        // Menú
        cout << "1. Despegar\n";
        cout << "2. Aterrizar\n";
        cout << "3. Girar a la derecha\n";
        cout << "4. Girar a la izquierda\n";
        cout << "0. Salir\n";

        cout << "Ingrese la opción: ";
        cin >> option;

        // Ejecutar comando correspondiente
        if (option != '0') {
            invoker.executeCommand(option);
        }

    } while (option != '0');

    return 0;
}
