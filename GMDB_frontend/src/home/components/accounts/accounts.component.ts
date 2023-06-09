import { Component } from '@angular/core';
import { ApiServiceService } from 'src/apiService/api-service.service';

@Component({
  selector: 'app-accounts',
  templateUrl: './accounts.component.html',
  styleUrls: ['./accounts.component.css'],
})
export class AccountsComponent {
  public mainValue = 0;
  public savingsValue = 0;
  public investValue = 0;

  constructor(private api: ApiServiceService) {
    this.api.InvestmentAccountValue$.subscribe((response) => {
      this.investValue = response;
    });

    this.api.MainAccountValue$.subscribe((response) => {
      this.mainValue = response;
    });

    this.api.SavingsAccountValue$.subscribe((response) => {
      this.savingsValue = response;
    });
  }
}
