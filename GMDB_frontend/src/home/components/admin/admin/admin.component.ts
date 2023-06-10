import { Component } from '@angular/core';
import { ApiServiceService } from 'src/apiService/api-service.service';
import { User } from 'src/models/User';
import { FormsModule } from '@angular/forms';

@Component({
  selector: 'app-admin',
  templateUrl: './admin.component.html',
  styleUrls: ['./admin.component.css']
})
export class AdminComponent {
  public users: User[] = [];

  constructor(private api: ApiServiceService) {
    this.fetchUserList();
  }

  fetchUserList() {
    this.api.UserList$.subscribe((response) => {
      this.users = response;
    });
  }

  updateUser(user: User) {
    this.api.UserList$.subscribe((response) => {
      this.users = response;
    });
  }
}
