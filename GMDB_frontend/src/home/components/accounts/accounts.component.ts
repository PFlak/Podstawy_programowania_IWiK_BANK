import { Component, OnInit } from '@angular/core';
import { ApiServiceService } from 'src/apiService/api-service.service';

@Component({
  selector: 'app-accounts',
  templateUrl: './accounts.component.html',
  styleUrls: ['./accounts.component.css'],
})

export class AccountsComponent implements OnInit {
  public name$: string = '';

  ngOnInit(): void {
    this.api.Name$.subscribe((response) => {
      this.name$ = response;
    });
  }

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
    this.api.getAccounts(this.name$).subscribe((response) => {
      console.log(response);
    });
  }
}
