import { Component } from '@angular/core';
import { ApiServiceService } from 'src/apiService/api-service.service';

@Component({
  selector: 'app-accounts',
  templateUrl: './accounts.component.html',
  styleUrls: ['./accounts.component.css'],
})
export class AccountsComponent {
  public mainValue: number | undefined = 0;
  public mainCurrency: string | undefined = 'PLN';
  public mainAccountNumber: string | undefined = '0000000001';

  public savingsValue: number | undefined = 0;
  public savingsCurrency: string | undefined = 'PLN';
  public savingsAccountNumber: string | undefined = '0000000002';

  public investValue: number | undefined = 0;
  public investCurrency: string | undefined = 'PLN';
  public investAccountNumber: string | undefined = '0000000003';

  constructor(private api: ApiServiceService) {
    this.api.InvestmentAccountValue$.subscribe((response) => {
      this.investValue = response.amount;
      this.investCurrency = response.currency;
      this.investAccountNumber = response.accountNumber;
    });

    this.api.MainAccountValue$.subscribe((response) => {
      this.mainValue = response.amount;
      this.mainCurrency = response.currency;
      this.mainAccountNumber = response.accountNumber;
    });

    this.api.SavingsAccountValue$.subscribe((response) => {
      this.savingsValue = response.amount;
      this.savingsCurrency = response.currency;
      this.savingsAccountNumber = response.accountNumber;
    });
  }
}