import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Router } from '@angular/router';
import { BehaviorSubject, Observable, Subscriber, subscribeOn } from 'rxjs';

import { User } from 'src/models/User';
import { Account } from 'src/models/Account';
import { History } from 'src/models/History';
import { getLocaleDateFormat } from '@angular/common';

@Injectable({
  providedIn: 'root',
})
export class ApiServiceService {
  private SERVER_DOMAIN = 'localhost:18080';

  //ONLY FOR ADMIN
  public UserList$: BehaviorSubject<User[]> = new BehaviorSubject<User[]>([]);

  public Name$: BehaviorSubject<string> = new BehaviorSubject<string>('');
  public Role$: BehaviorSubject<string> = new BehaviorSubject<string>('READER');

  public MainAccount$: BehaviorSubject<Account> = new BehaviorSubject<Account>({
    amount: 0,
    currency: '',
    accountNumber: '',
  });

  public InvestmentAccount$: BehaviorSubject<Account> =
    new BehaviorSubject<Account>({
      amount: 0,
      currency: '',
      accountNumber: '',
    });

  public SavingsAccount$: BehaviorSubject<Account> =
    new BehaviorSubject<Account>({
      amount: 0,
      currency: '',
      accountNumber: '',
    });

  public MainAccountValue$: BehaviorSubject<Account> =
    new BehaviorSubject<Account>({
      amount: 0,
      currency: '',
      accountNumber: '',
    });

  public InvestmentAccountValue$: BehaviorSubject<Account> =
    new BehaviorSubject<Account>({
      amount: 0,
      currency: '',
      accountNumber: '',
    });

  public SavingsAccountValue$: BehaviorSubject<Account> =
    new BehaviorSubject<Account>({
      amount: 0,
      currency: '',
      accountNumber: '',
    });

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
        if (role) {
          this.Role$.next(role);
        } else {
          this.setValueToMemory('U_R', 'READER');
          this.Role$.next('READER');
        }
        if (name) {
          this.Name$.next(name);
          this.getHistory(name).subscribe();
          this.getUserAccount(name).subscribe();
          this.getAllUsers().subscribe();
          subscriber.next(200);
        } else {
          subscriber.error(400);
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

  createUser(
    email: string,
    password: string,
    login: string,
    name: string,
    surname: string,
    personalCode: string,
    phoneNumber: string,
    isEmployee: string = 'false'
  ): Observable<number> {
    let observable: Observable<number> = new Observable<number>(
      (subscriber) => {
        this.http
          .post(`http://${this.SERVER_DOMAIN}/api/create_user`, {
            email: email,
            password: password,
            login: login,
            name: name,
            surname: surname,
            personalCode: personalCode,
            phoneNumber: phoneNumber,
            isEmployee: isEmployee,
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

                this.InvestmentAccount$.next({
                  amount: 0,
                  currency: '',
                  accountNumber: '',
                });
                this.InvestmentAccountValue$.next({
                  amount: 0,
                  currency: '',
                  accountNumber: '',
                });

                this.MainAccount$.next({
                  amount: 0,
                  currency: '',
                  accountNumber: '',
                });
                this.MainAccountValue$.next({
                  amount: 0,
                  currency: '',
                  accountNumber: '',
                });

                this.SavingsAccount$.next({
                  amount: 0,
                  currency: '',
                  accountNumber: '',
                });
                this.SavingsAccountValue$.next({
                  amount: 0,
                  currency: '',
                  accountNumber: '',
                });

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
            (error: any) => {
              subscriber.error(error.status);
            }
          );
      }
    );
    return observable;
  }

  updateUser(user: User): Observable<number> {
    let userModel: User = {
      name: user.name,
      surname: user.surname,
      mail: user.mail,
      personalCode: user.personalCode,
      phoneNumber: user.phoneNumber,
      role: user.role,
    };

    let role = user.role == 'ADMIN' ? 'true' : 'false';

    let observable = new Observable<number>((subscriber) => {
      this.http
        .post(`http://${this.SERVER_DOMAIN}/api/update_user`, {
          name: user.name,
          surname: user.surname,
          mail: user.mail,
          personalCode: user.personalCode,
          phoneNumber: user.phoneNumber,
          isEmploye: role,
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
  checkBalance(account: Account, type: 1 | 2 | 3): Observable<number> {
    let observable: Observable<number> = new Observable<number>(
      (subscriber) => {
        this.http
          .post(`http://${this.SERVER_DOMAIN}/api/check_balance`, {
            id: account,
          })
          .subscribe(
            (response: any) => {
              if (response.status == 'ok' && response.credits) {
                const accountValue: Account = {
                  amount: response.credits.amount,
                  currency: response.credits.currency,
                  accountNumber: response.credits.accountNumber,
                };

                switch (type) {
                  case 1:
                    this.MainAccountValue$.next(accountValue);
                    break;
                  case 2:
                    this.InvestmentAccountValue$.next(accountValue);
                    break;
                  case 3:
                    this.SavingsAccountValue$.next(accountValue);
                    break;
                }
                subscriber.next(200);
              } else {
                subscriber.error(400);
              }
            },
            (error: any) => {
              subscriber.error(error.status);
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
                  surname: response.users[i].email,
                  mail: response.users[i].email,
                  phoneNumber: response.users[i].email,
                  personalCode: response.users[i].email,
                  role: response.users[i].isEmployee ? 'USER' : 'ADMIN',
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

  getHistory(login: string): Observable<number> {
    let observable: Observable<number> = new Observable((subscriber) => {
      this.http
        .get(`http://${this.SERVER_DOMAIN}/api/get_history/${login}`)
        .subscribe(
          (response: any) => {
            if (response.status == 'ok' && response.history) {
              let listOfHistory: History[] = [];
              for (let i = 0; i < response.history.lenght; i++) {
                let history: History = {
                  from: response.history[i].from,
                  to: response.history[i].to,
                  amount: response.history[i].amount,
                  header: response.history[i].header,
                  info: response.history[i].info,
                  time: response.history[i].time,
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

  transfer(
    from: string,
    to: string,
    currency: string,
    amount: number,
    header: string,
    info: string
  ): Observable<number> {
    let observable: Observable<number> = new Observable<number>(
      (subscriber) => {
        this.http
          .post(`http://${this.SERVER_DOMAIN}/api/transfer`, {
            from: from,
            to: to,
            currency: currency,
            amount: amount,
            header: header,
            info: info,
            time: this.getCurrentDateTime(),
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

  getCurrentDateTime(): string {
    const now = new Date();

    const day = String(now.getDate()).padStart(2, '0');
    const month = String(now.getMonth() + 1).padStart(2, '0'); // January is 0
    const year = String(now.getFullYear());
    const hours = String(now.getHours()).padStart(2, '0');
    const minutes = String(now.getMinutes()).padStart(2, '0');

    const dateTimeString = `${day}.${month}.${year} ${hours}.${minutes}`;

    return dateTimeString;
  }
}
