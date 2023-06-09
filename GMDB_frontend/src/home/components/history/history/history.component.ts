import { Component } from '@angular/core';
import { ApiServiceService } from 'src/apiService/api-service.service';
import { History } from 'src/models/History';

@Component({
  selector: 'app-history',
  templateUrl: './history.component.html',
  styleUrls: ['./history.component.css'],
})
export class HistoryComponent {
  public history: History[] = [];

  constructor(api: ApiServiceService) {
    api.TransactionHistory$.subscribe((response) => {
      this.history = response;
    });
  }
}
