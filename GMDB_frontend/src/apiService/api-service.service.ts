import { Injectable } from '@angular/core';
import { HttpClient, HttpClientModule } from '@angular/common/http';
import { Router } from '@angular/router';
import { BehaviorSubject, Observable, Subscriber, subscribeOn } from 'rxjs';

import { User } from 'src/models/User';
import { Account } from 'src/models/Account';
import { History } from 'src/models/History';

@Injectable({
  providedIn: 'root',
})
export class ApiServiceService {
  private SERVER_DOMAIN = '192.168.1.30:18080';

  //ONLY FOR ADMIN
  public UserList$: BehaviorSubject<User[]> = new BehaviorSubject<User[]>([]);

  public Name$: BehaviorSubject<string> = new BehaviorSubject<string>('');
  public Role$: BehaviorSubject<string> = new BehaviorSubject<string>('READER');

  public MainAccount$: BehaviorSubject<string> = new BehaviorSubject<string>(
    ''
  );
  public MainAccountValue$: BehaviorSubject<number> =
    new BehaviorSubject<number>(0);

  public InvestmentAccount$: BehaviorSubject<string> =
    new BehaviorSubject<string>('');
  public InvestmentAccountValue$: BehaviorSubject<number> =
    new BehaviorSubject<number>(0);

  public SavingsAccount$: BehaviorSubject<string> = new BehaviorSubject<string>(
    ''
  );
  public SavingsAccountValue$: BehaviorSubject<number> =
    new BehaviorSubject<number>(0);

  public TransactionHistory$: BehaviorSubject<History[]> = new BehaviorSubject<
    History[]
  >([]);

  constructor(private http: HttpClient, private router: Router) {}

  setValueToMemory(key: string, value: string) {
    let encrypted_value = btoa(value);

    localStorage.setItem(key, encrypted_value);
  }

  getValueFromMemory(key: string): string | null {
    let value = localStorage.getItem(key);

    return value ? atob(value) : null;
  }

  deleteValueFromMemory(key: string) {
    localStorage.removeItem(key);
  }

  fetchData(): Observable<number> {
    let observable: Observable<number> = new Observable<number>(
      (subscriber) => {
        let name = this.getValueFromMemory('U_N');
        let password = this.getValueFromMemory('U_P');
        let role = this.getValueFromMemory('U_R');
        if (name) {
          this.Name$.next(name);
          this.getHistory(name).subscribe();
          this.getUserAccount(name).subscribe();
          this.getAllUsers().subscribe();
        }

        if (role) {
          this.Role$.next(role);
        }
      }
    );

    return observable;
  }

  apiCheck(): Observable<number> {
    let observable: Observable<number> = new Observable<number>(
      (subscriber) => {
        this.http.get(`http://${this.SERVER_DOMAIN}/check`).subscribe(
          (response: any) => {
            if (response == 'API Works!') {
              subscriber.next(200);
            } else {
              subscriber.error(400);
            }
          },
          (error: number) => {
            subscriber.next(error);
          }
        );
      }
    );

    return observable;
  }

  createUser(name: string, password: string): Observable<number> {
    let observable: Observable<number> = new Observable<number>(
      (subscriber) => {
        this.http
          .post(`http://${this.SERVER_DOMAIN}/api/create_user`, {
            email: name,
            password: password,
          })
          .subscribe(
            (response: any) => {
              if (response == 'ok') {
                subscriber.next(200);
              } else {
                subscriber.error(400);
              }
            },
            (error: number) => {
              subscriber.error(error);
            }
          );
      }
    );

    return observable;
  }

  loginUser(name: string, password: string): Observable<number> {
    let observable: Observable<number> = new Observable<number>(
      (subscriber) => {
        this.http
          .post(`http://${this.SERVER_DOMAIN}/api/login_user`, {
            email: name,
            password: password,
          })
          .subscribe(
            (response: any) => {
              if (response.status) {
                if (response.status == 'ok' && response.role) {
                  this.setValueToMemory('U_N', name);
                  this.setValueToMemory('U_R', response.role);
                  this.setValueToMemory('U_P', password);
                  this.Name$.next(name);
                  this.Role$.next(response.role);
                  subscriber.next(200);
                } else {
                  subscriber.error(400);
                }
              } else {
                subscriber.error(400);
              }
            },
            (error: number) => {
              subscriber.error(error);
            }
          );
      }
    );

    return observable;
  }

  logoutUser(name: string): Observable<number> {
    let observable: Observable<number> = new Observable<number>(
      (subscriber) => {
        this.http
          .post(`http://${this.SERVER_DOMAIN}/api/logout_user`, {
            email: name,
          })
          .subscribe(
            (response: any) => {
              if (response.status && response.status == 'ok') {
                this.Name$.next('');
                this.Role$.next('READER');

                this.InvestmentAccount$.next('');
                this.InvestmentAccountValue$.next(0);

                this.MainAccount$.next('');
                this.MainAccountValue$.next(0);

                this.SavingsAccount$.next('');
                this.SavingsAccountValue$.next(0);

                this.TransactionHistory$.next([]);
                this.UserList$.next([]);

                this.deleteValueFromMemory('U_N');
                this.deleteValueFromMemory('U_R');
                this.deleteValueFromMemory('U_P');
                subscriber.next(200);
              } else {
                subscriber.error(400);
              }
            },
            (error: number) => {
              subscriber.error(error);
            }
          );
      }
    );
    return observable;
  }

  updateUser(
    name: string | undefined,
    password: string | undefined,
    role: string | undefined
  ): Observable<number> {
    let name_ = name ? name : this.getValueFromMemory('U_N');
    let password_ = password ? password : this.getValueFromMemory('U_P');
    let role_ = role ? role : this.getValueFromMemory('U_R');

    let observable = new Observable<number>((subscriber) => {
      this.http
        .post(`http://${this.SERVER_DOMAIN}/api/update_user`, {
          email: name_,
          password: password_,
          role: role_,
        })
        .subscribe(
          (response: any) => {
            if (response.status && response.status == 'ok') {
              subscriber.next(200);
            } else {
              subscriber.error(400);
            }
          },
          (error: number) => {
            subscriber.error(error);
          }
        );
    });
    return observable;
  }

  /**
   *
   * @param account Account number
   * @param type 1 - Main Account, 2- Investment Account, 3- Savings Account
   */
  checkBalance(account: string, type: 1 | 2 | 3): Observable<number> {
    let observable: Observable<number> = new Observable<number>(
      (subscriber) => {
        this.http
          .post(`http://${this.SERVER_DOMAIN}/api/check_balance`, {
            id: account,
          })
          .subscribe(
            (response: any) => {
              if (response.status == 'ok' && response.credits) {
                switch (type) {
                  case 1:
                    this.MainAccountValue$.next(response.credits);
                    break;
                  case 2:
                    this.InvestmentAccountValue$.next(response.credits);
                    break;
                  case 3:
                    this.SavingsAccountValue$.next(response.credits);
                    break;
                }
                subscriber.next(200);
              }
              subscriber.error(400);
            },
            (error: number) => {
              subscriber.error(error);
            }
          );
      }
    );
    return observable;
  }

  getAllUsers(): Observable<number> {
    let observable: Observable<number> = new Observable((subscriber) => {
      this.http
        .get(`http://${this.SERVER_DOMAIN}/api/admin/get_all_users`)
        .subscribe(
          (response: any) => {
            if (response.status == 'ok' && response.users) {
              let listOfUsers: User[] = [];
              for (let i = 0; i < response.users.lenght; i++) {
                let user: User = {
                  name: response.users[i].email,
                  role: response.users[i].role,
                };
                listOfUsers.push(user);
              }
              this.UserList$.next(listOfUsers);
              subscriber.next(200);
            }
            subscriber.error(400);
          },
          (error: number) => {
            subscriber.error(error);
          }
        );
    });
    return observable;
  }

  getHistory(name: string): Observable<number> {
    let observable: Observable<number> = new Observable((subscriber) => {
      this.http
        .get(`http://${this.SERVER_DOMAIN}/api/get_history/${name}`)
        .subscribe(
          (response: any) => {
            if (response.status == 'ok' && response.history) {
              let listOfHistory: History[] = [];
              for (let i = 0; i < response.history.lenght; i++) {
                let history: History = {
                  from: response.history[i].from,
                  to: response.history[i].to,
                  amount: response.history[i].amount,
                };
                listOfHistory.push(history);
              }
              this.TransactionHistory$.next(listOfHistory);
              subscriber.next(200);
            }
            subscriber.error(400);
          },
          (error: number) => {
            subscriber.error(error);
          }
        );
    });
    return observable;
  }

  transfer(from: string, to: string, amount: number): Observable<number> {
    let observable: Observable<number> = new Observable<number>(
      (subscriber) => {
        this.http
          .post(`http://${this.SERVER_DOMAIN}/api/transfer`, {
            from: from,
            to: to,
            amount: amount,
          })
          .subscribe(
            (response: any) => {
              if (response.status && response.status == 'ok') {
                subscriber.next(200);
              } else {
                subscriber.error(400);
              }
            },
            (error: number) => {
              subscriber.error(error);
            }
          );
      }
    );
    return observable;
  }

  getUserAccount(name: string): Observable<number> {
    let observable: Observable<number> = new Observable<number>(
      (subscriber) => {
        this.http
          .post(`http://${this.SERVER_DOMAIN}/api/get_user_account`, {
            email: name,
          })
          .subscribe(
            (response: any) => {
              if (response.status == 'ok' && response.account) {
                for (let i = 0; i < response.account.lenght; i++) {
                  switch (response.account[i].type) {
                    case 1:
                      this.MainAccount$.next(response.account[i].id);
                      this.MainAccountValue$.next(response.account[i].amount);
                      break;
                    case 2:
                      this.InvestmentAccount$.next(response.account[i].id);
                      this.InvestmentAccountValue$.next(
                        response.account[i].amount
                      );
                      break;
                    case 3:
                      this.SavingsAccount$.next(response.account[i].id);
                      this.SavingsAccountValue$.next(
                        response.account[i].amount
                      );
                      break;
                  }
                }
                subscriber.next(200);
              }
              subscriber.error(400);
            },
            (error: number) => {
              subscriber.error(error);
            }
          );
      }
    );
    return observable;
  }
}
