export interface User {
  name?: string;
  password?: string;
  role?: 'USER' | 'ADMIN' | 'READER';
}
