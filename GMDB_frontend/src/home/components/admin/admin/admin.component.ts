import { Component } from '@angular/core';
import { ApiServiceService } from 'src/apiService/api-service.service';
import { User } from 'src/models/User';
import { FormsModule } from '@angular/forms';

@Component({
  selector: 'app-admin',
  templateUrl: './admin.component.html',
  styleUrls: ['./admin.component.css'],
})
export class AdminComponent {
  public users: User[] = [];

  constructor(private api: ApiServiceService) {
    let user1: User = {
      name: 'tester',
      surname: 'testowski',
      mail: 'tester@domain.com',
      personalCode: 12211110496,
      phoneNumber: 517267014,
      role: 'USER',
    };
    let user2: User = {
      name: 'tester',
      surname: 'testowski',
      mail: 'tester@domain.com',
      personalCode: 12211110496,
      phoneNumber: 517267014,
      role: 'ADMIN',
    };
    this.api.UserList$.subscribe((response) => {
      this.users = [user1, user2];
    });
  }

  updateUser(user: User) {
    this.api.updateUser(user);
  }

  upgrade(user: User) {
    user.role = 'ADMIN';

    this.api.updateUser(user).subscribe(
      (response) => {
        this.api.fetchData().subscribe();
      },
      (error) => {}
    );
  }

  downgrade(user: User) {
    user.role = 'USER';

    this.api.updateUser(user).subscribe(
      (response) => {
        this.api.fetchData().subscribe();
      },
      (error) => {}
    );
  }
}
