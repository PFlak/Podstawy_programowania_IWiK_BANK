import { Component, ElementRef, ViewChild } from '@angular/core';
import { ApiServiceService } from 'src/apiService/api-service.service';
import { Account } from 'src/models/Account';

@Component({
  selector: 'app-atm',
  templateUrl: './atm.component.html',
  styleUrls: ['./atm.component.css'],
})
export class AtmComponent {
  @ViewChild('mainBTN')
  private mainBTN!: ElementRef;

  @ViewChild('savingsBTN')
  private savingsBTN!: ElementRef;

  @ViewChild('investmentBTN')
  private investmentBTN!: ElementRef;

  @ViewChild('amountINPT')
  private amountINPT!: ElementRef;

  @ViewChild('headerINPT')
  private headerINPT!: ElementRef;

  @ViewChild('infoINPT')
  private infoINPT!: ElementRef;

  @ViewChild('payinBTN')
  private inBTN!: ElementRef;

  @ViewChild('payoutBTN')
  private outBTN!: ElementRef;

  public mainAccount: Account = { amount: 0, currency: '', accountNumber: '' }
  public savingsAccount: Account = { amount: 0, currency: '', accountNumber: '' };
  public investmentAccount: Account = { amount: 0, currency: '', accountNumber: '' };

  private accountDest: Account = { amount: 0, currency: 'PLN', accountNumber: '' };

  constructor(private api: ApiServiceService) {
    this.api.MainAccount$.subscribe((response) => {
      this.mainAccount = response;
      this.accountDest = response;
    });

    this.api.SavingsAccount$.subscribe((response) => {
      this.savingsAccount = response;
    });

    this.api.InvestmentAccount$.subscribe((response) => {
      this.investmentAccount = response;
    });

    this.api.MainAccountValue$.subscribe((response) => {
      this.mainAccount = response;
    });

    this.api.SavingsAccountValue$.subscribe((response) => {
      this.mainAccount = response;
    });

    this.api.InvestmentAccountValue$.subscribe((response) => {
      this.mainAccount = response;
    });
  }

  click1() {
    this.mainBTN.nativeElement.classList.add('clicked');
    this.mainBTN.nativeElement.classList.add('active');
    this.savingsBTN.nativeElement.classList.remove('active');
    this.investmentBTN.nativeElement.classList.remove('active');
    this.accountDest = this.mainAccount;
    setTimeout(() => {
      this.mainBTN.nativeElement.classList.remove('clicked');
    }, 300);
  }

  click2() {
    this.savingsBTN.nativeElement.classList.add('clicked');
    this.savingsBTN.nativeElement.classList.add('active');
    this.mainBTN.nativeElement.classList.remove('active');
    this.investmentBTN.nativeElement.classList.remove('active');
    this.accountDest = this.savingsAccount;
    setTimeout(() => {
      this.savingsBTN.nativeElement.classList.remove('clicked');
    }, 300);
  }

  click3() {
    this.investmentBTN.nativeElement.classList.add('clicked');
    this.investmentBTN.nativeElement.classList.add('active');
    this.savingsBTN.nativeElement.classList.remove('active');
    this.mainBTN.nativeElement.classList.remove('active');
    this.accountDest = this.investmentAccount;
    setTimeout(() => {
      this.investmentBTN.nativeElement.classList.remove('clicked');
    }, 300);
  }

  payin() {
    console.log(this.amountINPT.nativeElement.value);
    this.inBTN.nativeElement.classList.add('clicked');

    setTimeout(() => {
      this.inBTN.nativeElement.classList.remove('clicked');
    }, 300);

    if (this.accountDest != null && this.amountINPT.nativeElement.value) {
      this.api
        .transfer(
          this.accountDest.accountNumber,
          '000000000000000000',
          this.accountDest.currency,
          this.amountINPT.nativeElement.value,
          this.headerINPT.nativeElement.value,
          this.infoINPT.nativeElement.value
        )
        .subscribe(
          (response) => {
            this.inBTN.nativeElement.classList.add('success');

            setTimeout(() => {
              this.inBTN.nativeElement.classList.remove('success');
            }, 300);
            let type: 1 | 2 | 3;

            if (this.accountDest == this.mainAccount) {
              type = 1;
            } else if (this.accountDest == this.savingsAccount) {
              type = 2;
            } else {
              type = 3;
            }
            this.api.checkBalance(this.accountDest, type).subscribe();
          },
          (error) => {
            this.inBTN.nativeElement.classList.add('error');

            setTimeout(() => {
              this.inBTN.nativeElement.classList.remove('error');
            }, 300);
          }
        );
    } else {
      this.inBTN.nativeElement.classList.add('error');

      setTimeout(() => {
        this.inBTN.nativeElement.classList.remove('error');
      }, 300);
    }
  }
  payout() {
    this.outBTN.nativeElement.classList.add('clicked');

    setTimeout(() => {
      this.outBTN.nativeElement.classList.remove('clicked');
    }, 300);

    if (this.accountDest.amount != 0 && this.amountINPT.nativeElement.value) {
      this.api
        .transfer(
          this.accountDest.accountNumber,
          '000000000000000000',
          this.accountDest.currency,
          this.amountINPT.nativeElement.value,
          this.headerINPT.nativeElement.value,
          this.infoINPT.nativeElement.value
        )
        .subscribe(
          (response) => {
            this.outBTN.nativeElement.classList.add('success');

            setTimeout(() => {
              this.outBTN.nativeElement.classList.remove('success');
            }, 300);
            let type: 1 | 2 | 3;

            if (this.accountDest == this.mainAccount) {
              type = 1;
            } else if (this.accountDest == this.savingsAccount) {
              type = 2;
            } else {
              type = 3;
            }
            this.api.checkBalance(this.accountDest, type).subscribe();
          },
          (error) => {
            this.outBTN.nativeElement.classList.add('error');

            setTimeout(() => {
              this.outBTN.nativeElement.classList.remove('error');
            }, 300);
          }
        );
    } else {
      this.outBTN.nativeElement.classList.add('error');

      setTimeout(() => {
        this.outBTN.nativeElement.classList.remove('error');
      }, 300);
    }
  }
}
