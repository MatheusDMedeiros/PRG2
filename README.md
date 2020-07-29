```c++
case 1: {
                float nOnibus, lugar;
                vector<string> dados_cadastrar(3);

                cout << "Digite o número do ônibus que realizará sua viagem: ";
                cin >> nOnibus;

                // Busca se número do ônibus que realizará sua viagem está cadastrado
                auto busca_via = Busca_viagem(nOnibus);

                // Se número do ônibus existir
                if (busca_via != nullptr) {
                    cout << "Escolha seu assento de 0 a 42: ";
                    cin >> lugar;

                    // Testa se lugar é menor que é menor que 42
                    if (lugar > 42) {
                        cout << endl
                             << "Nossos ônibus possuem apenas 43 assento, favor escolher uma poltronas de 0 a 42"
                             << endl;
                    } else {
                        // Busca  se lugar da determinada viagem está ocupado
                        if (Busca_Lugar(busca_via, lugar)) {
                            cout << endl << "Certo, agora presisamos do seu nome e sobrenome para reservar seu assento na viagem."<< endl;
                            cout << "Nome: ";
                            cin >> dados_cadastrar[0];
                            cout << "Sobrenome: ";
                            cin >> dados_cadastrar[1];
                            dados_cadastrar[2] = dados_cadastrar[0] + " " + dados_cadastrar[1];

                            // Passa como parâmetro os dados , busca e lugar para reservar assento em uma viagem
                            auto id_pass = reservar(dados_cadastrar, busca_via, lugar);

                            cout << endl << "Seu ID é: " << id_pass << " e o Número da viagem é: " << nOnibus << endl;
                            cout << "Salve-os para consultar sua reserva quando quiser." << endl;

                        } else {
                            cout << endl << "O assento " << lugar
                                 << " já está ocupado ou está indisponível nessa viagem." << endl;
                        }
                    }
                } else {
                    //se número do ônibus não existir
                    cout << endl << "\t\t\tNão existe uma viagem com ônibus que possua o número => " << nOnibus << endl;
                    nEncontrado();
                }

            }
                pause();
                break;
            case 2: {
                viagensDisponiveis();
                pause();
                break;
            }

```
